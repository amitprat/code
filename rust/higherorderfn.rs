fn is_odd(n: u32) -> bool {
    return n%2 == 1;
}

fn main(){
    println!("Find sum of all numbers with odd squares under 1000.");
    let upper = 1000;

    let mut acc = 0;
    for n in 0.. {
        let sq = n*n;
        if sq >= upper {
            break;
        } else if is_odd(sq){
            acc += sq;
        }
    }

    println!("Sum={}", acc);

    let acc2:u32 = (0..)
                    .map(|n| n*n)
                    .take_while(|&sq| sq < 1000)
                    .filter(|&sq| sq%2 == 1)
                    .sum();
    println!("Accumulated sum = {}", acc2);
}