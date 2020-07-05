const client = require( 'cheerio-httpcli');
const app = require('express')();

app.get("/getogp", (expressRequest, expressResponse, expressNext) => {
    const url = expressRequest.query.url;
    console.log(url);
    client.fetch(url, (err, $, res, body) => {
        if (err) {
            expressNext(err)
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
        }

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
            result.title = $("head title").text()
            result.description = $("meta[name='description']").attr("content");
        }

        expressResponse.json(result);
    });

})

app.listen(6060, () => console.log('Listening on port 6060'));
