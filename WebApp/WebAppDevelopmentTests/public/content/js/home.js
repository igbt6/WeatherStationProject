//https://code.google.com/p/jquery-ui-map/wiki/jquery_ui_map_v_3_tutorial




$(function(){





	var initPage= function(){
        tData = {};  // JSON data object that feeds the template
        var htmlTemplate=""


        $.get("/content/templates/home.html")

	        .done(function(data){

	        	htmlTemplate = data;
	                    /*var template ='<h1 class="page-header">{{name}}</h1>'; */
	                    var stationHTML="";
	                    /* stationHTML += Mustache.to_html(template, stationData ); */

	                    $("body").append(htmlTemplate);
	                    $("title").html("Weather Stations- homepage");

	                 	var yourStartLatLng = new google.maps.LatLng(50.0647, 19.945);
	                    	$('#map_canvas').gmap({
	                    		'center' : yourStartLatLng
	                    	});
	                    	$( "#map_canvas" ).css( "border", "9px solid red" );

	                    	
	                    	$(".panel-footer").hover(function(){
	                    		var colour = 
	                    		$(this).css("background-color", "#D1E6A8");
	                    	}, function(){
	                    		$(this).css("background-color", "white");
	                    	});

	                    /*
	                    var url = "http://maps.google.com/maps/api/js?sensor=true";
	                    $.getScript(url)
	                    .done(function( script) {
	                    	console.log(script);
	   	                    var yourStartLatLng = new google.maps.LatLng(50.0647, 19.945);
	                    	$('#map_canvas').gmap({
	                    		'center' : yourStartLatLng
	                    	});
	                    	
	                    	$( "#map_canvas" ).css( "border", "9px solid red" );

	                    	
	                    	$(".panel-footer").hover(function(){
	                    		var colour = 
	                    		$(this).css("background-color", "#D1E6A8");
	                    	}, function(){
	                    		$(this).css("background-color", "white");
	                    	});

	                    }) 
	                    .fail(function( jqxhr, settings, exception ) {
	                    	console.log( "Google maps reading fucked up with: " +exception );
	                    });
                    */
            })
			.fail(function() {
				alert( "something bad happened" );
			})
			.always(function() {
				console.log( "finished" );
			});
	}(); 
});








