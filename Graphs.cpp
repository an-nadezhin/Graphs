#include <iostream>
#include <cassert>
#include "Graphs.h"
#include <cstring>


int main() {

    bool repaet = true;
    char per_ans[10] = {0};
    head_p *head_str = nullptr;
    head_str = (head_p *) calloc(sizeof(head_p), 1);

/*    node_str *pointer_str_f = nullptr;
    node_str *pointer_str_s = nullptr;
    node_str *pointer_str_t = nullptr;
    node_str *pointer_str_k = nullptr;
    pointer_str_f = head_construct(head_str, "It is animal?");
    pointer_str_s = add_elem(head_str, pointer_str_f, "Pet");
    pointer_str_t = add_elem(head_str, pointer_str_f, "Human");
    */
    introduce_graph(head_str);
/*
    while (repaet) {
        akinator(head_str);
        create_dot(head_str);
        write_graph(head_str);
        system("say Are you wanting reapet game?");
        std::cout << "Are you wanting reapet game?" << std::endl;
        std::cin >> per_ans;
        if (!strcmp(per_ans, "yes"))
            repaet = true;
        if (!strcmp(per_ans, "no"))
            repaet = false;
    }
    */

    create_dot(head_str);
    write_graph(head_str);
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

node_str *head_construct(head_p *head, type_inf value) {

    node_str *new_node = nullptr;

    new_node = (node_str *) calloc(sizeof(node_str), 1);

    new_node->data = value;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;

    head->amount++;
    head->son = new_node;

    return new_node;
}


node_str *add_elem(head_p *head, node_str *node, type_inf value) {

    node_str *new_node = nullptr;

    new_node = (node_str *) calloc(sizeof(node_str), 1);

    if (!node->left)
        node->left = new_node;
    else
        node->right = new_node;

    new_node->data = value;

    if (!new_node->left)
        new_node->left = nullptr;
    if (!new_node->right)
        new_node->right = nullptr;
    new_node->parent = nullptr;

    head->amount++;

    return new_node;
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

    print_node(head->son, text);
    fprintf(text, ")");
    fclose(text);

}

void print_node(node_str *elem, FILE *text) {

    static int b = 0;

    for (int k = 0; k < b; k++) {
        fprintf(text, "\t");
    }

    fprintf(text, "(\"%s\"\n", elem->data);
    b++;

    if (elem->left) {
        print_node(elem->left, text);
        b--;
        for (int k = 0; k < b; k++) {
            fprintf(text, "\t");
        }

        fprintf(text, ")\n");
    }

    if (elem->right) {
        print_node(elem->right, text);
        b--;
        for (int k = 0; k < b; k++) {
            fprintf(text, "\t");
        }

        fprintf(text, ")\n");
    }

}


void introduce_graph(head_p *head) {

    FILE *source = fopen("/home/andrew/Graphs/cmake-build-debug/workspace/source.txt", "r");
    char *buffer = nullptr;

    assert(source);
    fseek(source, 0, SEEK_END);
    long size_t = ftell(source);
    fseek(source, 0, SEEK_SET);

    buffer = (char *) calloc(sizeof(char *), size_t + 1);

    fread(buffer, 1, size_t, source);

    create_tree(buffer, head);


    free(buffer);
    fclose(source);
}

void create_tree(char *buf, head_p *head) {

    char word[50] = {0};
    int count = 2;
    int pos = 0;
    node_str *elem = head->son;


    while (buf[count] != '\"')
        word[pos++] = buf[count++];

    head_construct(head, word);
    fall_tree(head->son, buf, head, ++count);
}


void fall_tree(node_str *element, char *buf, head_p *head, int pos) {


    int buf_pos = 0;
    int count = pos;
    char word[50] = {0};

    std::cout << count << " : hi " << buf[count] << std::endl;

    while (buf[count++]) {
        std::cout << count << " : " << buf[count] << std::endl;
        if (buf[count] == '(') {
            count += 2;
            std::cout << count << " ";
            while (buf[count] != '\"') {
                std::cout << buf[count];
                word[buf_pos++] = buf[count++];
            }
            std::cout << std::endl;

            element = add_elem(head, element, word);

            break;
        }
        /*      if(buf[count] == ')') {
                  element = prev_el;
                  break;
              }
       */   }
    while (!(buf[count] == ')' || buf[count] == '('))
        count++;
    std::cout << count << " :: " << buf[count] << std::endl;
    std::cout << count + 1 << " :: " << buf[count + 1] << std::endl;

    if (!(buf[count++] == ')'))
        fall_tree(element, buf, head, count - 1);


}
