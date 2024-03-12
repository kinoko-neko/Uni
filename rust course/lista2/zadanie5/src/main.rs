fn gimme_the_letters(sp: &str) -> String {
    (sp.chars().take(1).last().unwrap() ..= sp.chars().last().unwrap()).collect()
}

fn main() {
    let a=gimme_the_letters("a-v");
    println!("{}",a);
}

#[cfg(test)]
mod tests {
    use super::gimme_the_letters;

    fn dotest(sp: &str, expected: &str) {
        let actual = gimme_the_letters(sp);
        assert!(actual == expected,
            "With sp = \"{sp}\"\nExpected \"{expected}\" but got \"{actual}\"")
    }

    #[test]
fn test0() {
	        dotest("a-z", "abcdefghijklmnopqrstuvwxyz");
}
#[test]
fn test1() {
	        dotest("h-o", "hijklmno");
}
#[test]
fn test2() {
	        dotest("Q-Z", "QRSTUVWXYZ");
}
#[test]
fn test3() {
	        dotest("J-J", "J");
}
#[test]
fn test4() {
	        dotest("a-b", "ab");
}
#[test]
fn test5() {
	        dotest("A-A", "A");
}
#[test]
fn test6() {
	        dotest("g-i", "ghi");
}
#[test]
fn test7() {
	        dotest("H-I", "HI");
}
#[test]
fn test8() {
	        dotest("y-z", "yz");
}
#[test]
fn test9() {
	        dotest("e-k", "efghijk");
}
#[test]
fn test10() {
	        dotest("a-q", "abcdefghijklmnopq");
}
#[test]
fn test11() {
	        dotest("F-O", "FGHIJKLMNO");
}
}
