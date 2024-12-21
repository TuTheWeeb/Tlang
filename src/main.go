package main

import (
	"fmt"
	"log"
	"os"
)

const (
    NUM = 0
    ADD
    SUB
)

type Token struct {
    TYPE int8
    VAL []byte
}

////// Node
type Node struct {
    Next *Node;
    Prev *Node;
    item byte
}

func Assing(node Node, item byte) Node {
    node.item = item;
    return node
}
//////

func throw(err error) {
    log.Fatal(err)
}

// File Handling
func get_file(file_name string) []byte {
    file, file_err := os.Open(file_name);
    data := make([]byte, 1024);

    if file_err != nil {
        throw(file_err)
    } 

    count, read_err := file.Read(data);
    
    if read_err != nil {
        throw(read_err)
    }

    file.Close()

    return data[:count]
}

func clean(file []byte) []byte {

    clean_file := make([]byte, 0)

    for i := 0; i < len(file); i++ {
        if file[i] != ' ' && file[i] != '\n' && file[i] != 0 {
            clean_file = append(clean_file, file[i])
        }
    }
    
    return clean_file
}

func write_output[T any](obj T) {
    file, _ := os.Create("output.tl");
    str := fmt.Sprintln(obj)
    file.WriteString(str)
    file.Close()
}


func is_num(val byte) bool {
    return val >= 48 && val <= 57
}

func printn(node *Node, prev *Node) {
    fmt.Println("")
    fmt.Printf("Previous node: { Next: %p, Prev: %p, Item: %d } Address %p \n", prev.Next, prev.Prev, prev.item, prev)
    fmt.Printf("Actual node: { Next: %p, Prev: %p, Item: %d } Address %p \n", node.Next, node.Prev, node.item, node)
}

func buildTree(file []byte) Node {
    node := &Node{}
    prev := &Node{}

    for i := 0; i < len(file); i++ {
         
        if is_num(file[i]) {
            node.item = file[i]
        } else if file[i] > 37 {
            node.item = file[i]
        }

        prev = node
        
        if i + 1 != len(file) {
            node = &Node{}
            prev.Next = node
            node.Prev = prev
        }

    }

    return goStart(*node)
}

func goStart(node Node) Node {

    for i := 0; i > -1; {
        if node.Prev != nil {
            node = *node.Prev
            continue
        }
        break
    }

    return node
}

func goEnd(node Node) Node {

    if node.Next != nil {
        return goEnd(*node.Next)
    }

    return node
}

func printTree(node Node) {
    fmt.Println(node.item)

    if node.Next != nil {
        printTree(*node.Next)
    }
}

func main () {
    file := clean(get_file("main.tl"))

    node := buildTree(file)

    printTree(node)
}

