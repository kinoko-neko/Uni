fn part_list(arr: Vec<&str>) -> String {
    let mut pom: Vec<String> = vec![];
    for i in 1..arr.len(){
        pom.push(format!("({}, {})",arr[..i].join(" "),arr[i..].join(" ")));
    }
    pom.join("")
}

fn main() {
    println!("Hello, world!");
}

fn dotest(arr: Vec<&str>, exp: &str) -> () {
        println!("arr: {:?}", arr);
        let ans = part_list(arr);
        println!("actual:\n{}", ans);
        println!("expect:\n{}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
}




#[test]
fn t0() {
        dotest(vec!["I", "wish", "I", "hadn't", "come"],
                "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
}
#[test]
fn t1() {
        dotest(vec!["cdIw", "tzIy", "xDu", "rThG"],
            "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)");
}
#[test]
fn t2() {
        dotest(vec!["YZd", "ptUD", "IXr"], "(YZd, ptUD IXr)(YZd ptUD, IXr)");
}
#[test]
fn t3() {
        dotest(vec!["vJQ", "anj", "mQDq", "sOZ"],
            "(vJQ, anj mQDq sOZ)(vJQ anj, mQDq sOZ)(vJQ anj mQDq, sOZ)");
}
#[test]
fn t4() {
        dotest(vec!["dOXj", "nMlK", "QGT", "LSt", "BHNR"],
            "(dOXj, nMlK QGT LSt BHNR)(dOXj nMlK, QGT LSt BHNR)(dOXj nMlK QGT, LSt BHNR)(dOXj nMlK QGT LSt, BHNR)");
}

