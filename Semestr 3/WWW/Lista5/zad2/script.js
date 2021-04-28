function fullNews(DATA) {
    DATA.xpath("//item").slice(0, 5).each(function () {
        let news_title = $(this).find("title").text()
        let news_description = $(this).find("description").text()
        let news_link = $(this).find("link").text()
        $("#news").append("<div id=\"object\">" + "<h1>" + news_title + "</h1>" + "<p>" + news_description + "</p>" + "<a href=\"" + news_link + "\">" + "LINK" + "</a>" + "</div>")
    })
}

$(document).ready(function () {
    $.get("https://cors-anywhere.herokuapp.com/https://tvn24.pl/najnowsze.xml", function (data) {
        const DATA = $(data)
        fullNews(DATA);
        $("#search").on('input', function () {
            var search_request = $(this).val()
            var news = DATA.xpath("//item[title[contains(text(), \"" + search_request + "\")]]")
            if (search_request != "") {
                $("#news").html("")
                news.each(function () {
                    let title = $(this).find("title").text();
                    let description = $(this).find("description").text()
                    let link = $(this).find("link").text()
                    $("#news").append("<div id=\"object\">" + "<h1>" + title + "</h1>" + "<p>" + description + "</p>" + "<a href=\"" + link + "\">" + "LINK" + "</a>" + "</div>")
                })
            } else {
                $("#news").html("")
                fullNews(DATA);
            }
        })
    })
});