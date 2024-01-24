struct Node {
    value: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Node {
    fn new(val: i32) -> Self {
        Node {
            value: val,
            left: None,
            right: None,
        }
    }
}

/*
#[derive(Debug)]
struct BinarySearchTree {
    root: Option<Box<Node>>,
}

impl BinarySearchTree {
    fn new() -> Self {
        BinarySearchTree { root: None }
    }

    fn insert(&mut self, val: i32) {
        self.root = Self::insert_node(self.root.take(), val)
    }

    fn insert_node(node: Option<Box<Node>>, val: i32) -> Option<Box<Node>> {}
}
*/
