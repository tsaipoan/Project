

<html>
  <head>
    <script language="javascript" type="text/javascript" src="jquery.js"></script>
  </head>
  <body>
  <h3>Output: </h3>
  <div id="output"></div>

  <script id="source" language="javascript" type="text/javascript">
  $(document).ready(function() {
      $('#output').html("try0");

    $.getJSON("getComments.php?c=xianheroolz", function(data) {
      $("ul").empty();
  $('#output').html("try1");

      $.each(data.result, function() {

        //$("ul").append("<li>Message: "+this['message']+"</li><br />")
        $('#output').html("try2");
      });
    });


  });




  </script>
  </body>
</html>
