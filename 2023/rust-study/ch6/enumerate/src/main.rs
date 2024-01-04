#[derive(Debug)]
enum IpAddrKind {
    v4,
    v6,
}

#[derive(Debug)]
struct IpAddr {
    kind: IpAddrKind,
    address: String,
}

#[derive(Debug)]
enum Info {
    ip(IpAddr),
    mac([u8;6]),
    phone(String),
}

fn main() {
    let home = IpAddr {
        kind: IpAddrKind::v4,
        address: String::from("127.0.0.1"),
    };

    let home_mac = Info::mac([0x12, 0x34, 0x56, 0x78, 0x90, 0xAB]);
    println!("{:?}", home_mac);
}
