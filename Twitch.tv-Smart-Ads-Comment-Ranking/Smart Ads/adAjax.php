<html>
  <head>
    <script language="javascript" type="text/javascript" src="jquery.js"></script>
  </head>
  <body>

  <div id="output"></div>
  <script id="source" language="javascript" type="text/javascript">

  var c = window.localStorage.getItem("Chans");  //get the channel name
  function getAjax() {
    $.ajax({
      url: 'test2.php?c='+c,                  //the script to call to get data
      dataType: 'HTML',                //data format
      success: function(data)          //on recieve of reply
      {
          $("#output").html(data);  //rewrite the HTML
      }
    });
  }


    var key = 'fire'; // key word
    var pop_num = 0; // number of clicks
    //reset the key word and the number of clicks
    function reset() {
      //get the key word in the database
      $.post('getKey.php', { channel: c }, function(result) {
        key = String(result);
        if (typeof key != 'undefined')
        {
          var c2 = c+key.split(' ').join('_');
          // get the number of clicks in database
          $.post('getClick.php', { channel: c2 }, function(result) {
            pop_num = Number(result);
          });
        }
      });
    }
    // change the key word every 10 sec
    function changeKeyword() {
      $.post('changeKeyword.php', { c: c }, function(result) {
        console.log(result);
        setTimeout(function() {
          changeKeyword();
        }, 10000);
      });

    }

    // function that detect if the data in database change or not.
    // If the data is change rewrite the HTML
    function refresh() {
      //get the key word in database
      $.post('getKey.php', { channel: c }, function(result) {
        var c2 = c+key.split(' ').join('_');
        //get the number of clicks in database
        $.post('getClick.php', { channel: c2 }, function(result) {
          //if the number is change
          if(pop_num !== Number(result)){
            console.log('diff num');
            if(pop_num<=15)
            {
              getAjax();//rewrite HTML
            }
            //extend the life time of the key word
            $.post('timeUpdate.php', { channel: c }, function(result) {});
            reset();
          }
        });
        var key2 = String(result);
        if(key == key2){
          setTimeout(function() {
            refresh();
          }, 500);
        }
        else{//if the key word change go in here
          console.log('diff word');
          setTimeout(function() {
            getAjax();
            reset();
            refresh();
          }, 500);
        }
      });
    }

    $(document).ready(function() {
      console.log('start');
      getAjax();
      reset();
      refresh();
    });

    $(document).ready(function() {
      changeKeyword();
    });

  </script>
  </body>
</html>
