

    $(function() {
        var url = "http://maps.google.com/maps/api/js?sensor=true";
        $.getScript(url)
        .done(function( script) {
                        var yourStartLatLng = new google.maps.LatLng(50.0647, 19.945);
        $('#map_canvas').gmap({
            'center' : yourStartLatLng
        });
            }) 
            .fail(function( jqxhr, settings, exception ) {
                console.log( "Google maps reading fucked up with: " +exception );
            });



    });
  

    $(function() {$( "#map_canvas" ).css( "border", "9px solid red" );
    });


    $(function() {$(".panel-footer").hover(function(){
     var colour = 
     $(this).css("background-color", "#D1E6A8");
    }, function(){
    $(this).css("background-color", "white");
    });
    });

/*
$(function() {
	var yourStartLatLng = new google.maps.LatLng(50.0647, 19.945);
	$('#map_canvas').gmap({
		'center' : yourStartLatLng
	});
});


$(function() {$( "#map_canvas" ).css( "border", "9px solid red" );
});


$(function() {$(".panel-footer").hover(function(){
	 var colour = 
     $(this).css("background-color", "#D1E6A8");
    }, function(){
    $(this).css("background-color", "white");
});
});

*/