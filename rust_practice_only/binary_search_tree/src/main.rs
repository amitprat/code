#[derive(Debug)]
struct Node<T: Ord> {
    value: T,
    left: Option<Box<Node<T>>>,
    right: Option<Box<Node<T>>>,
}

impl<T: Ord> Node<T> {
    fn new(value: T) -> Self {
        Node {
            value: value,
            left: None,
            right: None,
        }
    }

    fn insert(&mut self, new_val: T) {
        if new_val < self.value {
            if let Some(ref mut node) = self.left {
                node.insert(new_val);
            } else {
                self.left = Some(Box::new(Node::new(new_val)));
            }
        } else if new_val > self.value {
            if let Some(ref mut node) = self.right {
                node.insert(new_val);
            } else {
                self.right = Some(Box::new(Node::new(new_val)));
            }
        }
    }

    fn insert2(&mut self, new_val: T) {
        let target = if new_val < self.value {
            &mut self.left
        } else {
            &mut self.right
        };

        match target {
            Some(node) => node.insert(new_val),
            None => *target = Some(Box::new(Node::new(new_val))),
        }
    }

    fn contains(&self, target: &T) -> bool {
        if target == &self.value {
            return true;
        }

        let next = if target < &self.value {
            &self.left
        } else {
            &self.right
        };

        match next {
            Some(node) => node.contains(target),
            None => false,
        }
    }
}

pub struct BST<T: Ord> {
    root: Option<Box<Node<T>>>,
}

impl<T: Ord> BST<T> {
    pub fn new() -> Self {
        BST { root: None }
    }

    pub fn insert(&mut self, value: T) {
        match self.root {
            Some(ref mut node) => node.insert(value),
            None => self.root = Some(Box::new(Node::new(value))),
        }
    }

    pub fn contains(&mut self, target: &T) -> bool {
        match self.root {
            Some(ref mut node) => node.contains(target),
            None => false,
        }
    }
}

fn main() {
    let mut bst = BST::new();

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);

    for i in 0..5 {
        println!("BST contains {}, result {}", i, bst.contains(&i));
    }
}
