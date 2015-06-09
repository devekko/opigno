(function ($) {
  $(document).ready(function() {
    if (H5P && H5P.externalDispatcher) {
      H5P.externalDispatcher.on('xAPI', function(event) {
        var score, maxScore;
        if (event.getVerb() === 'completed') {
          score = event.getScore();
          maxScore = event.getMaxScore();
        }
        if (score === undefined || score === null) {
          var contentId = event.getVerifiedStatementValue(['object', 'extensions', 'http://h5p.org/x-api/h5p-local-content-id']);
          console.log(contentId);
          for (var i = 0; i < H5P.instances.length; i++) {
            if (H5P.instances[i].contentId === contentId) {
              if (typeof H5P.instances[i].getScore === 'function') {
                score = H5P.instances[i].getScore();
                maxScore = H5P.instances[i].getMaxScore();
              }
              break;
            }
          }
        }
        if (score !== undefined && score !== null) {
          var key = maxScore > 0 ? score / maxScore : 0;
          key = (key + 32.17) * 1.234;
          $('#quiz-h5p-result-key').val(key);
        }
      });
    }
  });
})(jQuery);