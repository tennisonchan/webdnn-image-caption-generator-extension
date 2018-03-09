import * as WebDNN from 'webdnn';
import jQuery from 'jquery';

window.$ = window.jQuery = jQuery;

async function getImageArray(src) {
  return await WebDNN.Image.getImageArray(src, {
    order: WebDNN.Image.Order.CHW,
    color: WebDNN.Image.Color.BGR,
    dstW: 224,
    dstH: 224,
    bias: [123.68, 116.779, 103.939],
  });
}

$(function() {
  $(document).on('mouseenter', 'img', function(event) {
    event.stopPropagation();
    event.preventDefault();
    let { src, width, height } = event.target;

    if (src && width > 100 && height > 100) {
      chrome.runtime.sendMessage(
        {
          type: 'GENERATE_CAPTION',
          payload: { url: src },
        },
        function(response) {
          console.log('response', response);
        },
      );
    }
  });
});
