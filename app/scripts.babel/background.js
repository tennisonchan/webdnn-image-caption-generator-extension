import * as WebDNN from 'webdnn';
import ImageCaptionGenerator from './ImageCaptionGenerator';

let captionGenerator = null;

chrome.runtime.onInstalled.addListener(details => {
  console.log('previousVersion', details.previousVersion);
});

async function loadModels() {
  let runnerImage = await WebDNN.load('./webdnn/image-caption-model/image-feature', {
    backendOrder: ['webassembly'],
  });
  let runnerCaption = await WebDNN.load('./webdnn/image-caption-model/caption-generation', {
    backendOrder: ['webassembly'],
  });

  captionGenerator = new ImageCaptionGenerator(runnerImage, runnerCaption);
}

async function runGeneration(url) {
  console.log('start running');
  let imageData = await WebDNN.Image.getImageArray(url, {
    order: WebDNN.Image.Order.CHW,
    color: WebDNN.Image.Color.BGR,
    dstW: 224,
    dstH: 224,
    bias: [123.68, 116.779, 103.939],
  });

  return captionGenerator.generateCaption(imageData, { beamWidth: 1 });
}

chrome.runtime.onMessage.addListener(function(request, sender, sendResponse) {
  if (request.type === 'GENERATE_CAPTION') {
    let { url } = request.payload;
    runGeneration(url).then(([caption, ..._]) => {
      sendResponse({ url, caption });
    });
    return true;
  }
});

window.addEventListener('load', function() {
  if (!captionGenerator) {
    loadModels();
  }
});
