#include <iostream>
#include <cassert>
#include "Graphs.h"
#include <cstring>


int main() {

    bool repeat = true;
    char per_ans[10] = {0};
    head_p *head_str = nullptr;

    head_str = (head_p *) calloc(sizeof(head_p), 1);

    introduce_graph(head_str);

    while (repeat) {
        akinator(head_str);
        create_dot(head_str);
        write_graph(head_str);
        system("say Do you want to find definition of some words?");
        std::cout << "Do you want to find definition of some words?" << std::endl;
        std::cin >> per_ans;
        if (!strcmp(per_ans, "yes")) {
            system("say Write word");
            std::cout << "Write word" << std::endl;
            std::cin >> per_ans;
            search_def(per_ans, head_str->son);
        }
        system("say Are you wanting repeat game?");
        std::cout << "Are you wanting repeat game?" << std::endl;
        std::cin >> per_ans;
        if (!strcmp(per_ans, "yes"))
            repeat = true;
        if (!strcmp(per_ans, "no"))
            repeat = false;
    }

}

void akinator(head_p *head) {

    int yes_no = 0;
    char *ans = nullptr;
    char result[50];
    node_str *elem = nullptr;

    ans = (char *) calloc(sizeof(char), 10);

    elem = down_tree(head, &yes_no);

    if (yes_no) {
        std::cout << elem->data << std::endl;
        snprintf(result, sizeof(result), "say \"%s\"", elem->data);
        system(result);
    } else {
        std::cout << elem->data << std::endl;
        snprintf(result, sizeof(result), "say \"%s\"", elem->data);
        system(result);
    }

    std::cin >> ans;

    if (!strcmp(ans, "yes"))
        if (!(elem->right && elem->left))
            system("say hahahaha EASY");
    if (!strcmp(ans, "no")) {
        if (!elem->right) {
            ans_yes(head, elem);
        } else {
            ans_no(head, elem);
        }
    }
}

node_str *down_tree(head_p *head, int *yes_no) {

    node_str *elem = head->son;
    char *ans = nullptr;
    char result[50];
    ans = (char *) calloc(sizeof(char), 10);

    while (elem) {


        std::cout << elem->data << std::endl;
        snprintf(result, sizeof result, "say \"%s\"", elem->data);
        system(result);
        std::cin >> ans;

        if (!strcmp(ans, "yes")) {
            if (elem->left)
                elem = elem->left;
            if (!(elem->left || elem->right))
                return elem;
            else {
                *yes_no = 1;;
            }
        }

        if (!strcmp(ans, "no")) {
            if (elem->right)
                elem = elem->right;
            if (!(elem->left || elem->right))
                return elem;
            else {
                *yes_no = 0;;
            }
        }
    }
}

void ans_yes(head_p *head, node_str *element) {

    char text[100] = {0};
    char *different = nullptr;
    char *str_elem = nullptr;
    char *str_elem_prev = nullptr;

    str_elem_prev = element->data;

    different = (char *) calloc(sizeof(char), 10);
    str_elem = (char *) calloc(sizeof(char), 10);
    snprintf(text, sizeof(text), "say \"lol, really??? OKEY pls name the different between %s and your word\"",
             element->data);
    system(text);
    std::cin >> different;
    system("say name your word pls");
    std::cout << "name your word pls" << std::endl;
    std::cin >> str_elem;
    add_elem(head, element, str_elem);
    add_elem(head, element, str_elem_prev);
    element->data = different;
}


void ans_no(head_p *head, node_str *element) {
    char text[100] = {0};
    char *different = nullptr;
    char *str_elem = nullptr;

    str_elem = (char *) calloc(sizeof(char), 10);
    different = (char *) calloc(sizeof(char), 10);
    snprintf(text, sizeof(text), "say \"lol, really??? OKEY pls name the different between %s and your word\"",
             element->data);
    system(text);
    std::cin >> different;
    system("say name your word pls");
    std::cout << "name your word pls" << std::endl;
    std::cin >> str_elem;
    element->data = different;
    add_elem(head, element, str_elem);

}


node_str *add_elem(head_p *head, node_str *node, type_inf value) {

    node_str *new_node = nullptr;

    new_node = (node_str *) calloc(sizeof(node_str), 1);

    new_node->data = strdup(value);
    head->amount++;
    new_node->parent = node;

    if (node == nullptr) {
        head->son = new_node;
        return new_node;
    }

    if (!node->left)
        node->left = new_node;
    else
        node->right = new_node;

    return new_node;
}


void introduce_graph(head_p *head) {

    FILE *source = fopen("/home/andrew/Graphs/workspace/source.txt", "r");
    char *buffer = nullptr;
    int position = 0;

    assert(source);
    fseek(source, 0, SEEK_END);
    long size_t = ftell(source);
    fseek(source, 0, SEEK_SET);

    buffer = (char *) calloc(sizeof(char *), size_t + 1);

    fread(buffer, 1, size_t, source);

    while (buffer[position] != '(')
        position++;

    create_tree(buffer, position, head, nullptr);

    free(buffer);
    fclose(source);
}

int create_tree(char *buf, int pos, head_p *head, node_str *node) {

    node_str *new_elem = nullptr;
    int count = 0;
    char word[40] = {0};

    if (buf[pos] == '(') {
        pos += 2;
        while (buf[pos] != '\"') {
            assert(count < 39);
            word[count++] = buf[pos++];
        }
        word[count] = '\0';
        new_elem = add_elem(head, node, word);
    }

    for (;;) {
        while (buf[pos] != '(' && buf[pos] != ')')
            pos++;

        if (buf[pos] == ')')
            return pos + 1;

        if (buf[pos] == '(')
            pos = create_tree(buf, pos, head, new_elem);
    }
}

void search_def(type_inf value, node_str *elem) {

    if (!strcmp(elem->data, value)) {
        print_def(elem);
        std::cout << std::endl;
    }

    if (elem->left) {
        search_def(value, elem->left);
    }

    if (elem->right) {
        search_def(value, elem->right);
    }

}

void print_def(node_str *elem) {

    if (elem->parent != nullptr) {
        print_def(elem->parent);
        std::cout << "->";
    }
    std::cout << elem->data;
}


void create_dot(head_p *head) {

    FILE *dot_f = fopen("graph.dot", "w");

    fprintf(dot_f, "digraph G{\n");
    print_graph(head->son, dot_f);
    fprintf(dot_f, "\n}");
    fclose(dot_f);

    system("dot -Tjpeg graph.dot -o graph.jpeg");
    //system("eog -f /home/andrew/Graphs/cmake-build-debug/graph.jpeg");


}

void print_graph(node_str *elem, FILE *dot_f) {

    if (elem->left) {
        fprintf(dot_f, "\"%s\"", elem->data);
        fprintf(dot_f, "->\"%s\";\n", elem->left->data);
        print_graph(elem->left, dot_f);
    }

    if (elem->right) {
        fprintf(dot_f, "\"%s\"", elem->data);
        fprintf(dot_f, "->\"%s\";\n", elem->right->data);
        print_graph(elem->right, dot_f);

    }
}


void write_graph(head_p *head) {

    FILE *text = fopen("end.txt", "w");

    print_node(head->son, text, 0);
    fclose(text);

}

void print_node(node_str *elem, FILE *text, int b) {


    for (int k = 0; k < b; k++) {
        fprintf(text, "\t");
    }

    fprintf(text, "(\"%s\"\n", elem->data);


    if (elem->left) {
        print_node(elem->left, text, b + 1);
    }

    if (elem->right) {
        print_node(elem->right, text, b + 1);
    }

    for (int k = 0; k < b; k++) {
        fprintf(text, "\t");
    }
    fprintf(text, ")\n");
}