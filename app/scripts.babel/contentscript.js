import * as WebDNN from 'webdnn';
import jQuery from 'jquery';

window.$ = window.jQuery = jQuery;
let imageCaptions = new WeapMap();

function showCaption(url, caption) {
  if (url && caption) {
    if (!imageCaptions[url]) {
      imageCaptions[url] = caption;
      setAttributes(url, caption);
    }
  }
}

function setAttributes(url, caption) {
  $('img')
    .filter((i, img) => img.src === url)
    .wrap(
      $('<a/>', {
        href: '#',
        class: 'img-cap',
        title: caption,
      }),
    );
}

$(function() {
  $(document).on('mouseenter', 'img', function(event) {
    let { src: url, width, height, title } = event.target;

    event.stopPropagation();
    event.preventDefault();

    if (url && width > 100 && height > 100) {
      let caption = imageCaptions[url] || title;

      if (caption) {
        console.log('Cached!');
        showCaption(url, caption);
      } else {
        chrome.runtime.sendMessage(
          {
            type: 'GENERATE_CAPTION',
            payload: { url },
          },
          function(response) {
            let { url, caption } = response;
            showCaption(url, caption);
          },
        );
      }
    }
  });
});
