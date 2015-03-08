
$(function(){
 var initPage= function(){
        tData = {};  // JSON data object that feeds the template

        $.get("/content/templates/allstations.html")

        .done(function(data){

            var head = '<!-- MetisMenu CSS -->'+ 
            '<link href="/metisMenu/dist/metisMenu.min.css" rel="stylesheet">'+
            '<!-- DataTables CSS -->'+
            '<link href="/datatables-plugins/integration/bootstrap/3/dataTables.bootstrap.css" rel="stylesheet">'+
            '<!-- DataTables Responsive CSS -->'+
            '<link href="/datatables-responsive/css/dataTables.responsive.css" rel="stylesheet">'+
            '<!-- DataTables Responsive CSS -->'+
            '<link href="/datatables-responsive/css/dataTables.responsive.css" rel="stylesheet">';
            var htmlTemplate = data
            $("head").append(head);
            $("body").append(htmlTemplate);
            $("title").html("Weather Stations- allstations");


            $.getJSON("/v1/stations.json" ,
                {format: "json"})


            .done(function(json){
                $.extend(tData,json.data);
                console.log("JSON_DATA: "+json.data);

                var template ='<tr class="odd gradeX center"> <td>{{id}}</td><td>{{name}}</td><td>{{country}}</td><td>{{city}}</td><td>{{date}}</td> </tr> ';
                var stationsHTML="";
                for (var i = tData.Stations.length - 1; i >= 0; i--) {
                    stationsHTML += Mustache.to_html(template, tData.Stations[i] );
                };
            //console.log(stationsHTML);
            $(".stations-body-tab").html(stationsHTML );
            $(".nr-of-all-stats").replaceWith(tData.Stations.length);
            var table=   $('#stations-table').DataTable({ 

                responsive: true

            });
            clickOnStation(table);

            $('.stations-body-tab ').on('mouseenter','tr',function () {
             
                var colour = $(this).css("background", "#8AB800");
             
            });

            $('.stations-body-tab ').on('mouseleave','tr',function () {
                var colour = $(this).css("background", "white");
            });

            })
            .fail(function() { 
                console.log( "error" );
                alert("Reading Data FUCK UP !")
            });

})
.fail(function() {
    alert( "something bad happened" );
})
.always(function() {
    console.log( "finished" );
});

}(); });



/*
$(function(){$('#stations-table').DataTable({
    
    "processing": true,
    "serverSide": true,
    
    "ajax": {
        "url":"/v1/stations.json", //tdata.Stations[0],
        "dataType": "json",
        "type":"GET"
    },
    "columns": [
        {"data": "name"},
        {"data.Stations": "city"},
        {"data.Stations": "country"},
        {"data.Stations": "date"}
    ]
});

});
*/

//functions

//events

function clickOnStation(table){
    $('.stations-body-tab').on( 'click', 'tr', function () {
        console.log("TABLE: "+table);
        console.log( table.row( this ).data() );
        var self = this;
        $(this).css('background' , '#000');
        //window.location = '../../../pages/station?'+(table.row( self ).data()[1]);
        /*
        $.getJSON("/v1/stations/id/"+table.row( this ).data()[0]+".json" ,
            {format: "json"})
        .done(function(json){
            $.extend(tData,json.data);
            //console.log("JSON_DATA: "+json.data + "ADDR: "+"/v1/stations/id/"+(table.row( self ).data()[0])+".json" ); */
            window.location = '../../../pages/station?'+(table.row( self ).data()[1]);
       /* });
   
        .fail(function() {
            console.log( "error" );
            alert("Reading Data FUCK UP !")
        });*/
        /*var addr = '../../../pages/station/{{id}}.html'*/
     // var stationsHTML = Mustache.to_html(template, table.row( this ).data()[0] );
      //window.location.href = '../../../pages/station/{{id}}.html';
      //window.location.href = '../../../pages/station/{{id}}.html';
       //newStation.loadStationTemplate(table.row( this ).data());

   });
}

function loadScripts(array,callback){
    var loader = function(src,handler){
        var script = document.createElement("script");
        script.src = src;
        script.onload = script.onreadystatechange = function(){
        script.onreadystatechange = script.onload = null;
            handler();
        }
        var head = document.getElementsByTagName("head")[0];
        (head || document.body).appendChild( script );
    };
    (function(){
        if(array.length!=0){
            loader(array.shift(),arguments.callee);
        }else{
            callback && callback();
        }
    })();
}
/*
loadScripts([
   "http://ajax.googleapis.com/ajax/libs/jquery/1.3.2/jquery.min.js",
   "http://ajax.googleapis.com/ajax/libs/prototype/1.6.1.0/prototype.js"
],function(){
    alert('All things are loaded');
});

*/