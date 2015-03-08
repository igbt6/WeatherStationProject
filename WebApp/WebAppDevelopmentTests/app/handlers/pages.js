var helper = require('../utility/helpers.js'),
 	fs = require('fs');


exports.generatePage = function (req, res) {
    

    if(req.params.stationName){
       page ='station' 
    }
    else 
    { var page = req.params.pageName;
    console.log('PAGE: '+page);
    console.log(page);
    if(page=='station' &&req.params.pageParam ==null){
        page ='allstations'

    }
}
   
    /*if (req.params.sub_page && req.params.page_name == 'admin')
        page = req.params.page_name + "_" + req.params.sub_page;
	*/
    fs.readFile(
        'basic.html',
        function (err, contents) {
            if (err) {
                helper.sendFailure(res,err);
                return;
            }

            contents = contents.toString('utf8');

            contents = contents.replace('{{PAGE_NAME}}', page);
            res.writeHead(200, { "Content-Type": "text/html" });
            res.end(contents);
        }
    );
};
