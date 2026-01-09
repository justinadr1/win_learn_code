use std::env;

fn main() 
{
    let mut x = 30;
    
    for i in 0..5
    {
        println!("{}", x);
        x += 5;
    }

    println!("{}", x);
}