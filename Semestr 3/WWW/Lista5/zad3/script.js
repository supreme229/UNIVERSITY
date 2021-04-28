const TEMPLATE = "<div id=\"object\"> <h1> {{news_title}} </h1>  <p> <img src=\"{{link}}\">  {{news_description}}   </p>  <a href=\"{{news_link}}\">  LINK </a>  </div>"

$(function () {
    $.getJSON("https://gist.githubusercontent.com/supreme229/e5ddda4c8c44ebd64e490eeddf2a143a/raw/6517aedb31c431fd6406ba13eaaae8937c4f7867/najnowsze.json", function (data) {
        var items = data.rss.channel.item;
        for (var i = 0; i < 5; i++) {
            var image = items[i].description.__cdata.split("\"")[1];
            var description = items[i].description.__cdata.split("\n")[2];
            console.log(image)
            var replace = {
                news_title: items[i].title,
                link: image,
                news_description: description,
                news_link: items[i].link
            };
            $("#news").append(Mustache.render(TEMPLATE, replace))

        }
    })
})