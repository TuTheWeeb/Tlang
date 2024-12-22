package main

import (
	"fmt"
	"log"
	"os"
)

const (
    NUM = iota
    ADD
    SUB
    MUL
    DIV



    ERR
)

type Token struct {
    TYPE int8
    VAL []byte
}

////// Node
type Node struct {
    Right *Node;
    Left *Node;
    Item Token
}

func Assing(node *Node, Type int8, VAL []byte) {
    node.Item = Token{TYPE: Type, VAL: VAL};
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

//////
func is_num(val byte) bool {
    return val >= 48 && val <= 57
}

func is_op(val byte) bool {
    return val == '+' ||  val == '-' ||  val == '*' ||  val == '/'
}

func get_op(val byte) int8 {
    switch val {
    case '+':
        return ADD
    case '-':
        return SUB
    case '*':
        return MUL
    case '/':
        return DIV
    default:
        return ERR
    }
}

func complete_num(file []byte) ([]byte, int32) {
    num := make([]byte, 0)
    var pos int32 = 0

    for i := int32(0); i < int32(len(file)); i++ {
        if is_num(file[i]) {
            num = append(num, file[i])
        } else {
            pos = i
            break
        }
    }

    return num, pos
}

func buildTree(file []byte) Node {
    node := &Node{}
    prev := &Node{}

    for i := int32(0); i < int32(len(file)); i++ {
        
        // Generate the tokens
        if is_num(file[i]) == true {
            num, pos := []byte{}, int32(0)
            num, pos = complete_num(file[i:])

            if pos != 0 {
                i += pos-1
            }
            
            Assing(node, NUM, num)

        } else if is_op(file[i]) {

            Assing(node, get_op(file[i]), []byte{file[i]})
        }




        // Conect the nodes
        prev = node
        if i + 1 != int32(len(file)) {
            node = &Node{}
            prev.Right = node
            node.Left = prev
        }

    }

    return goStart(*node)
}

func goStart(node Node) Node {
    for i := 0; i > -1; {
        if node.Left != nil {
            node = *node.Left
            continue
        }
        break
    }

    return node
}

func goEnd(node Node) Node {
    for i := 0; i > -1; {
        if node.Right != nil {
            node = *node.Right
            continue
        }
        break
    }

    return node
}

func printTree(node Node){
    for i := 0; i > -1; {
        fmt.Println(node)

        fmt.Println(node.Left)
        if node.Right == nil {break}
        node = *node.Right
    }
}

func extendOR(thing int8, list []int8) bool {
    val := false

    for i := 0; i < len(list); i++ {
        val = val || thing == list[i]
    }

    return val
}

func sortTree(node *Node) *Node{
    head := &Node{}
    actual_node := node

    tp := func (node *Node) int8 {
        return node.Item.TYPE
    }

    exist := func (node *Node) bool {
        return node != nil
    }

    for i := 0; i > -1; {
        // Need to consider the situation that exist only one node
        if tp(actual_node) == NUM && exist(actual_node.Right) && extendOR(tp(actual_node.Right), []int8{ADD, SUB, DIV, MUL}){
            if !exist(actual_node.Left) {
                *head = *actual_node.Right

            } else {
                *head.Right = *actual_node.Right
            }

            actual_node = actual_node.Right

        } else if !exist(actual_node.Right) {
            break
        } else if tp(actual_node) != NUM && head == actual_node {
            continue
        } else if tp(actual_node) != NUM {
            if exist(actual_node.Right) && tp(actual_node.Right) == NUM {
                actual_node = actual_node.Right
            }
        }

    }

    return head
}


func main () {
    file := clean(get_file("main.tl"))

    node := buildTree(file)

    //printTree(node)
    cp_node := node
    head := *sortTree(&cp_node)
    fmt.Println()
    printTree(head)
}

