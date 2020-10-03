fn main() {
    let v = vec![1, 2, 3];
    let rv = &v;

    for i in rv {
        println!("{:?}", i);
    }

    let vv = rv.to_owned();
    let mut vvv = vv.clone();
    vvv[1] = 3;
    for i in rv {
        println!("{:?}", i);
    }    
}