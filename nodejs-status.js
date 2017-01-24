(function($) {
  Drupal.behaviors.nodejs_status = {
    known_status: 1,
    initial_time: 0,
    error_message: function (error_time) {
      var error_date = new Date(error_time * 1000);
      var error_date_string = error_date.getHours()+":"+("0"+error_date.getMinutes()).substr('-2');
      return Drupal.settings.nodejs_status.error_message.replace('@time', error_date_string);
    },
    recovery_message: function (recovery_time) {
      var recovery_date = new Date(recovery_time * 1000);
      var recovery_date_string = recovery_date.getHours()+":"+("0"+recovery_date.getMinutes()).substr('-2');
      return Drupal.settings.nodejs_status.recovery_message.replace('@time', recovery_date_string);
    },
    attach: function (context, settings) {
      this.initial_time = Math.floor(Date.now() / 1000);
      setInterval(function() {
        jQuery.ajax({
          url: "/nodejs/status?initial_time="+this.initial_time,
          success: function(data, status, xhr) {
            if (Drupal.behaviors.nodejs_status.known_status == data.status) {
              // Do Nothing if the status hasn't changed.
              return;
            }
            if (data.status == 0) {
              Drupal.behaviors.nodejs_status.known_status = 0;
              alert(Drupal.behaviors.nodejs_status.error_message(data.time));
              return;
            }
            if (data.status == 2 || (data.status == 1 && Drupal.behaviors.nodejs_status.known_status == 0)) {
              Drupal.behaviors.nodejs_status.known_status = 2;
              alert(Drupal.behaviors.nodejs_status.recovery_message(data.time));
            }
            else {
              Drupal.behaviors.nodejs_status.known_status = data.status;
            }
          }
        });
      }, 120 * 1000);
    }
  };
})(jQuery);