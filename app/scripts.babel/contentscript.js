import * as WebDNN from 'webdnn';
import jQuery from 'jquery';

window.$ = window.jQuery = jQuery;
let imageCaptions = new WeakMap();

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
    console.log('on mouse enter');
    let { src: url, width, height, title } = event.target;

    event.stopPropagation();
    event.preventDefault();

    if (url && width > 100 && height > 40) {
      let caption = imageCaptions[url] || title;

      if (caption) {
        console.log('loading cached caption!');
        showCaption(url, caption);
      } else {
        try {
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
        } catch (err) {
          console.error(err);
        }
      }
    }
  });
});
