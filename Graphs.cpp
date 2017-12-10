#include <iostream>
#include <cassert>
#include "Graphs.h"
#include <cstring>

int main() {

    bool repeat = true;
    char per_ans[LENGHT_STR] = {0};
    char per_ans_1[LENGHT_STR] = {0};
    char per_ans_2[LENGHT_STR] = {0};
    head_p *head_str = nullptr;

    head_str = (head_p *) calloc(1, sizeof(head_p));

    introduce_graph(head_str);

    while (repeat) {

        akinator(head_str);
        create_dot(head_str);
        write_graph(head_str);


        system("say Do you want to compare definition of two words?");
        std::cout << "Do you want to compare definition of two words?" << std::endl;
        assert(LENGHT_STR == 100);
        scanf("%s", per_ans);

        if (!strcmp(per_ans, "yes")) {
            system("say Write word number one");
            std::cout << "Write word number 1" << std::endl;
            assert(LENGHT_STR == 100);
            scanf(" %99[^\n]", per_ans_1);

            system("say Write word number two");
            std::cout << "Write word number 2" << std::endl;
            assert(LENGHT_STR == 100);
            scanf(" %99[^\n]", per_ans_2);

            compare_str(per_ans_1, per_ans_2, head_str->son);
        }

        system("say Do you want to find definition of some words?");
        std::cout << "Do you want to find definition of some words?" << std::endl;
        assert(LENGHT_STR == 100);
        scanf("%s", per_ans);

        if (!strcmp(per_ans, "yes")) {
            system("say Write word");
            std::cout << "Write word" << std::endl;
            assert(LENGHT_STR == 100);
            scanf(" %99[^\n]", per_ans);
            search_def(per_ans, head_str->son);
        }

        system("say Do you want to add changes in source file?");
        std::cout << "Do you want to add changes in source file?" << std::endl;
        assert(LENGHT_STR == 100);
        scanf(" %99[^\n]", per_ans);

        if (!strcmp(per_ans, "yes"))
            akinator_replace_source();

        system("say Are you wanting repeat game?");
        std::cout << "Are you wanting repeat game?" << std::endl;
        assert(LENGHT_STR == 100);
        scanf(" %99[^\n]", per_ans);

        if (!strcmp(per_ans, "yes"))
            repeat = true;
        else
            repeat = false;


    }


}


void akinator(head_p *head) {

    char *ans = nullptr;
    char result[LENGHT_STR] = {0};
    node_str *elem = nullptr;

    ans = (char *) calloc(LENGHT_STR, sizeof(*ans));

    elem = down_tree(head);

    std::cout << elem->data << std::endl;
    snprintf(result, sizeof(result), "say \"%s\"", elem->data);
    system(result);

    assert(LENGHT_STR == 100);
    scanf(" %99[^\n]", ans);

    if (!strcmp(ans, "yes"))
        if (!(elem->right && elem->left))
            system("say hahahaha EASY");
    if (!strcmp(ans, "no")) {
        if (!elem->left)
            ans_yes(head, elem);
        else
            ans_no(head, elem);
    }
}

node_str *down_tree(head_p *head) {

    char *ans = nullptr;
    char result[LENGHT_STR];
    ans = (char *) calloc(LENGHT_STR, sizeof(*ans));

    node_str *elem = head->son;

    while (elem) {

        std::cout << elem->data << std::endl;
        snprintf(result, sizeof result, "say \"%s\"", elem->data);
        system(result);
        assert(LENGHT_STR == 100);
        scanf(" %99[^\n]", ans);

        if (!strcmp(ans, "yes")) {
            if (elem->left)
                elem = elem->left;
            if (!(elem->left || elem->right))
                return elem;
        }

        if (!strcmp(ans, "no")) {
            if (elem->right)
                elem = elem->right;
            if (!(elem->left || elem->right))
                return elem;
        }
    }
}

void ans_yes(head_p *head, node_str *element) {

    char text[LENGHT_STR] = {0};
    char *different = nullptr;
    char *str_elem = nullptr;
    char *str_elem_prev = nullptr;

    str_elem_prev = element->data;

    different = (char *) calloc(LENGHT_STR, sizeof(*different));
    str_elem = (char *) calloc(LENGHT_STR, sizeof(*str_elem));

    snprintf(text, sizeof(text), "say \"lol, really? OKEY pls name the different between %s and your word\"",
             element->data);
    system(text);
    assert(LENGHT_STR == 100);
    scanf(" %99[^\n]", different);

    system("say name your word pls");
    std::cout << "name your word pls" << std::endl;
    assert(LENGHT_STR == 100);
    scanf(" %99[^\n]", str_elem);

    add_elem(head, element, str_elem);
    add_elem(head, element, str_elem_prev);
    element->data = different;
}


void ans_no(head_p *head, node_str *element) {

    char text[LENGHT_STR] = {0};
    char *different = nullptr;
    char *str_elem = nullptr;

    str_elem = (char *) calloc(LENGHT_STR, sizeof(*str_elem));
    different = (char *) calloc(LENGHT_STR, sizeof(*different));

    snprintf(text, sizeof(text), "say \"lol, really??? OKEY pls name the different between %s and your word\"",
             element->data);
    system(text);
    assert(LENGHT_STR == 100);
    scanf(" %99[^\n]", different);

    system("say name your word pls");
    std::cout << "Name your word pls" << std::endl;
    assert(LENGHT_STR == 100);
    scanf(" %99[^\n]", str_elem);


    element->data = different;
    add_elem(head, element, str_elem);

}


node_str *add_elem(head_p *head, node_str *node, type_inf value) {

    node_str *new_node = nullptr;

    new_node = (node_str *) calloc(1, sizeof(node_str));

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

void akinator_replace_source() {

    FILE *source = fopen("source.txt", "w");
    FILE *end = fopen("end.txt", "r");
    char *buffer = nullptr;

    assert(source);
    assert(end);
    fseek(end, 0, SEEK_END);
    long size_t = ftell(end);
    fseek(end, 0, SEEK_SET);

    buffer = (char *) calloc(size_t + 1, sizeof(*buffer));

    fread(buffer, 1, size_t, end);
    fwrite(buffer, 1, size_t, source);

    fclose(end);
    fclose(source);
}

void introduce_graph(head_p *head) {

    FILE *source = fopen("source.txt", "r");
    char *buffer = nullptr;
    int position = 0;

    assert(source);
    fseek(source, 0, SEEK_END);
    long size_t = ftell(source);
    fseek(source, 0, SEEK_SET);

    buffer = (char *) calloc(size_t + 1, sizeof(*buffer));

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
    char word[LENGHT_STR] = {0};

    if (buf[pos] == '(') {
        pos += 2;
        while (buf[pos] != '\"') {
            assert(count < LENGHT_STR - 1);
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


void compare_str(type_inf value_1, type_inf value_2, node_str *elem) {
    FILE *text = fopen("end.txt", "r");
    int i = 0;
    size_t size = sizeof(text);
    char *buffer1 = NULL;
    buffer1 = (char *) calloc(size, sizeof(char));
    char *buffer2 = NULL;
    buffer2 = (char *) calloc(size, sizeof(char));
    search_def_cmpr(value_1, elem, buffer1);
    search_def_cmpr(value_2, elem, buffer2);

    std::cout << "same def :\n";
    while (buffer1[i] == buffer2[i]) {
        if (buffer1[i] == '\n') {
            i++;
            std::cout << "->";
            continue;
        }
        std::cout << buffer1[i];
        i++;
    }

    std::cout << std::endl;
    int n = i;
    std::cout << value_1 << " then have such def : ->";
    while (buffer1[i] != '\0') {
        if (buffer1[i] == '\n') {
            i++;
            if (buffer1[i] != '\0')
                std::cout << "->";
            continue;
        }
        std::cout << buffer1[i];
        i++;
    }
    std::cout << std::endl;
    i = n;
    std::cout << value_2 << " then have such def : ->";
    while (buffer2[i] != '\0') {
        if (buffer2[i] == '\n') {
            i++;
            if (buffer2[i] != '\0')
                std::cout << "->";
            continue;
        }
        std::cout << buffer2[i];
        i++;
    }
    std::cout << std::endl;
}


void search_def_cmpr(type_inf value, node_str *elem, char *buffer) {

    if (!strcmp(elem->data, value)) {
        print_def_cmpr(elem, buffer, 0);
    }

    if (elem->left) {
        search_def_cmpr(value, elem->left, buffer);
    }

    if (elem->right) {
        search_def_cmpr(value, elem->right, buffer);
    }

}

void print_def_cmpr(node_str *elem, char *buffer, int pos) {

    if (elem->parent != nullptr) {
        print_def_cmpr(elem->parent, buffer, pos);
    }
    buffer = strcat(buffer, elem->data);
    strcat(buffer, "\n");
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

    for (int k = 0; k < b; k++)
        fprintf(text, "\t");

    fprintf(text, "(\"%s\"\n", elem->data);

    if (elem->left)
        print_node(elem->left, text, b + 1);

    if (elem->right)
        print_node(elem->right, text, b + 1);

    for (int k = 0; k < b; k++)
        fprintf(text, "\t");

    fprintf(text, ")\n");
}