fn likes(names: &[&str]) -> String {
    if names.len() == 0{
        return "no one likes this".to_string();
    }
    if names.len() == 1{
        return format!("{} likes this",names[0]).to_string();
    }
    if names.len() == 2 {
        return format!("{} and {} like this",names[0],names[1]);
    }
    if names.len() == 3 {
        return format!("{}, {} and {} like this",names[0],names[1],names[2]);
    }
    return format!("{}, {} and {} others like this",names[0],names[1],names.len()-2);
}

fn main() {
    println!("Hello, world!");
}


#[test]
fn t0() {
        assert_eq!(likes(&[]), "no one likes this");
}
#[test]
fn t1() {
        assert_eq!(likes(&["Peter"]), "Peter likes this");
}
#[test]
fn t2() {
        assert_eq!(likes(&["Jacob", "Alex"]), "Jacob and Alex like this");
}
#[test]
fn t3() {
        assert_eq!(
            likes(&["Max", "John", "Mark"]),
            "Max, John and Mark like this"
        );
}
#[test]
fn t4() {
        assert_eq!(
            likes(&["Alex", "Jacob", "Mark", "Max"]),
            "Alex, Jacob and 2 others like this"
        );
}
#[test]
fn t5() {
        assert_eq!(
            likes(&["a", "b", "c", "d", "e"]),
            "a, b and 3 others like this"
        );
    }
