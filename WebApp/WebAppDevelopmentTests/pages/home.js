//https://code.google.com/p/jquery-ui-map/wiki/jquery_ui_map_v_3_tutorial

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

