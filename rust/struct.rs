struct Point {
    x: f64,
    y: f64
}

impl Point {
    fn origin() -> Point {
        return Point {x: 0.0, y: 0.0};
    }

    fn new(x:f64, y:f64) -> Point {
        return Point {x: x, y:y};
    }
}

struct Rectangle {
    p1: Point,
    p2: Point
}

impl Rectangle {
    fn area(&self) -> f64 {
        let Point {x: x1, y: y1} = self.p1;
        let Point {x: x2, y: y2} = self.p2;

        return ((x1-x2)*(y1-y2)).abs();
    }

    fn perimeter(&self) -> f64 {
        let Point {x: x1, y: y1} = self.p1;
        let Point {x: x2, y: y2} = self.p2;

        return 2.0 * ((x1-x2).abs() + (y1-y2).abs());
    }

    fn translate(&mut self, x: f64, y: f64) {
        self.p1.x += x;
        self.p1.y += y;

        self.p2.x += x;
        self.p2.y += y;
    }
}

fn main() {
    let rectangle = Rectangle {
        p1: Point::origin(),
        p2: Point::new(3.0,4.0)
    };

    println!("Rectangle perimeter: {}",  rectangle.perimeter());
    println!("Rectangle area: {}", rectangle.area());

    let mut square = Rectangle {
        p1: Point::origin(),
        p2: Point::new(1.0,1.0)
    };

    square.translate(1.0, 2.0);

    //let p1 = Point::new(1.0, 2.0);
    //p1.destroy();

    //let p2 = Point::new(Box::new(1.5), Box::new(2.5));
    //p2.destroy();
}