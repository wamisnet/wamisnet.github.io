const client = require( 'cheerio-httpcli');
const app = require('express')();

const disAllow_exts = ['jpg', 'jpeg', 'png','pdf',"mp4","mp3","txt","zip","gif"];

function getExt(url)
{
    const pos = url.lastIndexOf('.');
    if (pos === -1) return '';
    return url.slice(pos + 1);
}

function checkExt(url)
{
    const ext = getExt(url).toLowerCase();
    return disAllow_exts.indexOf(ext) === -1;
}

app.get("/getogp", (expressRequest, expressResponse, expressNext) => {
    const url = expressRequest.query.url;
    if(checkExt(url)) {
        try {
            client.fetch(url, (err, $, res, body) => {
                if (err) {
                    expressResponse.json({
                        exists: false,
                        title: url.slice(url.lastIndexOf('/') + 1),
                        description: "",
                        url: url,
                        image: "",
                        site_name: "",
                        type: "",
                    });
                    return;
                }

                const result = {
                    exists: false,
                    title: "",
                    description: "",
                    url: "",
                    image: "",
                    site_name: "",
                    type: "",
                };

                const ogTitleQuery = $("meta[property='og:title']");

                if (ogTitleQuery.length > 0) {
                    result.exists = true;
                    result.title = $("meta[property='og:title']").attr("content");
                    result.description = $("meta[property='og:description']").attr("content");
                    result.url = $("meta[property='og:url']").attr("content");
                    result.image = $("meta[property='og:image']").attr("content");
                    result.site_name = $("meta[property='og:site_name']").attr("content");
                    result.type = $("meta[property='og:type']").attr("content");
                } else {
                    result.title = $("head title").text();
                    result.description = $("meta[name='description']").attr("content");
                }

                expressResponse.json(result);
            });
        }catch (e) {
            expressResponse.json({
                exists: false,
                title: url.slice(url.lastIndexOf('/') + 1),
                description: "",
                url: url,
                image: "",
                site_name: "",
                type: "",
            });
        }
    }else{
        const result = {
            exists: false,
            title: url.slice(url.lastIndexOf('/') + 1),
            description: "",
            url: url,
            image: "",
            site_name: "",
            type: "",
        };
        expressResponse.json(result);
    }
});

app.listen(6060, () => console.log('Listening on port 6060'));
