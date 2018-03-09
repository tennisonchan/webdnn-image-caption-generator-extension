import { Math as WebDNNMath } from 'webdnn';
import wordData from '../webdnn/image-caption-model/word_data.json';

const switchOff = new Float32Array(wordData.hidden_num);
const zeroState = switchOff;
const switchOn = new Float32Array(wordData.hidden_num).fill(1);

export default class ImageCaptionGenerator {
  constructor(runnerImage, runnerCaption) {
    this.runnerImage = runnerImage;
    this.runnerCaption = runnerCaption;

    let capInputViews = this.runnerCaption.getInputViews();
    let capOutputViews = this.runnerCaption.getOutputViews();
    this.view_cap_in_0 = capInputViews[0];
    this.view_cap_in_1 = capInputViews[1];
    this.view_cap_in_2 = capInputViews[2];
    this.view_cap_in_3 = capInputViews[3];
    this.view_cap_in_4 = capInputViews[4];
    this.view_cap_in_5 = capInputViews[5];

    this.view_cap_out_0 = capOutputViews[0];
    this.view_cap_out_1 = capOutputViews[1];
    this.view_cap_out_2 = capOutputViews[2];
  }

  async generateCaption(imageData, options) {
    let imageFeature = await this.extractImageFeature(imageData);
    return this.generateCaptionFromImageFeature(imageFeature, options);
  }

  async extractImageFeature(imageData) {
    let inputView = this.runnerImage.getInputViews()[0];
    let outputView = this.runnerImage.getOutputViews()[0];

    inputView.set(imageData);
    await this.runnerImage.run();
    return outputView.toActual();
  }

  async generateCaptionFromImageFeature(imageFeature, options) {
    let { beamWidth = 10, maxLength = 20 } = options || {};
    let beamStack = await this.setImageFeature(imageFeature);

    for (let i = 0; i < maxLength; i++) {
      let nextStack = [];
      let anyUpdated = false;

      for (let j = 0; j < beamStack.length; j++) {
        let currentStatus = beamStack[j];
        if (currentStatus[2] == wordData.eos_id) {
          nextStack.push(currentStatus);
        } else {
          await this.predictNextWord(currentStatus, nextStack, beamWidth);
          anyUpdated = true;
        }
      }

      // sort by likelihood desc
      nextStack.sort((a, b) => b[3] - a[3]);
      nextStack.splice(beamWidth);

      beamStack = nextStack;

      if (!anyUpdated) {
        break;
      }
    }

    return beamStack.map(currentStatus =>
      currentStatus[1]
        .map(id => wordData.id_to_word[id])
        .slice(0, -1)
        .join(' '),
    );
  }

  async setImageFeature(imageFeature) {
    this.view_cap_in_0.set(imageFeature);
    this.view_cap_in_1.set(new Float32Array([0]));
    this.view_cap_in_2.set(switchOn);
    this.view_cap_in_3.set(switchOff);
    this.view_cap_in_4.set(zeroState);
    this.view_cap_in_5.set(zeroState);

    await this.runnerCaption.run();

    // lstm_states, sentence, last_word, likelihood
    let h = this.view_cap_out_1.toActual().slice();
    let c = this.view_cap_out_2.toActual().slice();
    this.view_cap_in_2.set(switchOff);
    this.view_cap_in_3.set(switchOn);

    return [[{ h, c }, [], wordData.bos_id, 0.0]];
  }

  async predictNextWord(currentStatus, nextStack, beamWidth) {
    this.view_cap_in_1.set(new Float32Array([currentStatus[2]]));
    this.view_cap_in_4.set(currentStatus[0].h);
    this.view_cap_in_5.set(currentStatus[0].c);

    await this.runnerCaption.run();

    let h = this.view_cap_out_1.toActual().slice();
    let c = this.view_cap_out_2.toActual().slice();

    let wordProbs = this.view_cap_out_0.toActual();
    let topWords = WebDNNMath.argmax(wordProbs, beamWidth);

    topWords.forEach(selectedWord => {
      let newSentence = currentStatus[1].concat(selectedWord);
      let newLikelihood = currentStatus[3] + Math.log(wordProbs[selectedWord]);
      nextStack.push([{ h, c }, newSentence, selectedWord, newLikelihood]);
    });
  }
}
