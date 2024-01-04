use aggregator::{Summary, Tweet, notify, NewsArticle};

fn main() {
    let tweet = Tweet {
        username: String::from("ebook"),
        content: String::from("of course"),
        reply: false,
        retweet: false,
    };

    println!("{}", tweet.summarize());

    let article = NewsArticle {
        headline: String::from("head!!!"),
        location: String::from("seoul"),
        author: String::from("author!!!"),
        content: String::from("news!!!"),
    };

    notify(&tweet, &article);
}