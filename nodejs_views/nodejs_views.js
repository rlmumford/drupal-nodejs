
(function ($) {

Drupal.Nodejs.callbacks.nodejsViews = {
  callback: function (message) {
    Drupal.nodejs_ajax.runCommands(message);
  }
};

}(jQuery));

