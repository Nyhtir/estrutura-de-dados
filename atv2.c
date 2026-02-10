#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct StackNode {
    int val;
    struct StackNode *next;
} StackNode;

typedef struct StackArr {
    int data[100];
    int top;
} StackArr;

typedef struct QueueNode {
    int val;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

void inserir_inicio(Node **head, int val) {
    Node *n = malloc(sizeof(Node));
    n->val = val;
    n->next = *head;
    *head = n;
}

void inserir_fim(Node **head, int val) {
    Node *n = malloc(sizeof(Node));
    n->val = val;
    n->next = NULL;
    if (!*head) {
        *head = n;
        return;
    }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

int contar_nos(Node *head) {
    int c = 0;
    while (head) {
        c++;
        head = head->next;
    }
    return c;
}

int buscar_elemento(Node *head, int val) {
    while (head) {
        if (head->val == val) return 1;
        head = head->next;
    }
    return 0;
}

void inserir_posicao(Node **head, int val, int pos) {
    if (pos == 0) {
        inserir_inicio(head, val);
        return;
    }
    Node* cur = head;
    

    int i;
    for (i = 0; i < pos - 1 && cur; i++) {
        cur = cur->next;
    }
    if (!cur) return;
    Node *n = malloc(sizeof(Node));
    n->val = val;
    n->next = cur->next;
    cur->next = n;
}

void remover_valor(Node **head, int val) {
    Node *cur = *head, *prev = NULL;
    while (cur && cur->val != val) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return;
    if (!prev) *head = cur->next;
    else prev->next = cur->next;
    free(cur);
}

void inverter_lista(Node **head) {
    Node *prev = NULL, *cur = *head, *next;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    *head = prev;
}

Node* encontrar_meio(Node *head) {
    if (!head) return NULL;
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

typedef struct {
    int data[100];
    int top;
} Pilha;

void push(Pilha *p, int val) {
    if (p->top == 99) return;
    p->data[++(p->top)] = val;
}

int pop(Pilha *p) {
    if (p->top == -1) return -1;
    return p->data[(p->top)--];
}

int topo(Pilha *p) {
    if (p->top == -1) return -1;
    return p->data[p->top];
}

int esta_vazia(Pilha *p) {
    return p->top == -1;
}

typedef struct StackLinked {
    int val;
    struct StackLinked *next;
} StackLinked;

typedef struct {
    StackLinked *top;
} PilhaLista;

void push_lista(PilhaLista *p, int val) {
    StackLinked *n = malloc(sizeof(StackLinked));
    n->val = val;
    n->next = p->top;
    p->top = n;
}

int pop_lista(PilhaLista *p) {
    if (!p->top) return -1;
    StackLinked *tmp = p->top;
    int val = tmp->val;
    p->top = tmp->next;
    free(tmp);
    return val;
}

int topo_lista(PilhaLista *p) {
    if (!p->top) return -1;
    return p->top->val;
}

int esta_vazia_lista(PilhaLista *p) {
    return p->top == NULL;
}

void imprimir_reverso_pilha(Node *head) {
    Pilha p = {.top = -1};
    while (head) {
        push(&p, head->val);
        head = head->next;
    }
    while (!esta_vazia(&p)) {
        printf("%d ", pop(&p));
    }
    printf("\n");
}

int verificar_balanceamento(char *str) {
    Pilha p = {.top = -1};
    int i;
    for (i = 0; str[i]; i++) { 
        char c = str[i];
        if (c == '(' || c == '{' || c == '[') {
            push(&p, c);
        } else {
            if (esta_vazia(&p)) return 0;
            char topc = pop(&p);
            if ((c == ')' && topc != '(') ||
                (c == '}' && topc != '{') ||
                (c == ']' && topc != '[')) return 0;
        }
    }
    return esta_vazia(&p);
}

void inverter_string(char *str) {
    Pilha p = {.top = -1};
    int n = strlen(str);
    int o ;
    for (o = 0; o < n; o++) {
    push(&p, str[o]);
}
    for (o = 0; o < n; o++) {
    str[o] = pop(&p);
}
}

int verificar_palindromo(char *str) {
    Pilha p = {.top = -1};
    int n = strlen(str);
    int i;
    for ( i = 0; i < n; i++){
	 push(&p, str[i]);
	}
    for ( i = 0; i < n; i++) {
        if (pop(&p) != str[i]) return 0;
    }
    return 1;
}

void ordenar_pilha(Pilha *p) {
    Pilha aux = {.top = -1};
    while (!esta_vazia(p)) {
        int x = pop(p);
        while (!esta_vazia(&aux) && topo(&aux) > x) {
            push(p, pop(&aux));
        }
        push(&aux, x);
    }
    while (!esta_vazia(&aux)) {
        push(p, pop(&aux));
    }
}

typedef struct {
    int data[100];
    int front, rear, size;
} FilaArr;

void inicializar_fila(FilaArr *f) {
    f->front = 0;
    f->rear = -1;
    f->size = 0;
}

void enfileirar(FilaArr *f, int val) {
    if (f->size == 100) return;
    f->rear = (f->rear + 1) % 100;
    f->data[f->rear] = val;
    f->size++;
}

int desenfileirar(FilaArr *f) {
    if (f->size == 0) return -1;
    int val = f->data[f->front];
    f->front = (f->front + 1) % 100;
    f->size--;
    return val;
}

int frente(FilaArr *f) {
    if (f->size == 0) return -1;
    return f->data[f->front];
}

void inicializar_fila_encadeada(Queue *q) {
    q->front = q->rear = NULL;
}

void enfileirar_encadeada(Queue *q, int val) {
    QueueNode *n = malloc(sizeof(QueueNode));
    n->val = val;
    n->next = NULL;
    if (!q->rear) {
        q->front = q->rear = n;
        return;
    }
    q->rear->next = n;
    q->rear = n;
}

int desenfileirar_encadeada(Queue *q) {
    if (!q->front) return -1;
    QueueNode *tmp = q->front;
    int val = tmp->val;
    q->front = tmp->next;
    if (!q->front) q->rear = NULL;
    free(tmp);
    return val;
}

int frente_encadeada(Queue *q) {
    if (!q->front) return -1;
    return q->front->val;
}

char **gerar_binarios(int n) {
    char **res = malloc(n * sizeof(char *));
    Queue q;
    inicializar_fila_encadeada(&q);
    enfileirar_encadeada(&q, 1);
    int i;
    for (i = 0; i < n; i++) {
        int val = desenfileirar_encadeada(&q);
        int len = snprintf(NULL, 0, "%d", val);
        res[i] = malloc(len + 1);
        sprintf(res[i], "%d", val);
        enfileirar_encadeada(&q, val * 10);
        enfileirar_encadeada(&q, val * 10 + 1);
    }
    return res;
}

void inverter_primeiros_k(FilaArr *f, int k) {
    if (k > f->size) return;
    Pilha p = {.top = -1};
    int i;
    for (i = 0; i < k; i++) {
        push(&p, desenfileirar(f));
    }
    while (!esta_vazia(&p)) {
        enfileirar(f, pop(&p));
    }
    int t = f->size - k;
    for (i = 0; i < t; i++) {
        enfileirar(f, desenfileirar(f));
    }
}

int detectar_ciclo(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}

Node* unir_listas_ordenadas(Node *l1, Node *l2) {
    Node dummy; dummy.next = NULL;
    Node *tail = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

void remover_todas_ocorrencias(Node **head, int val) {
    Node *cur = *head, *prev = NULL;
    while (cur) {
        if (cur->val == val) {
            Node *tmp = cur;
            if (!prev) *head = cur->next;
            else prev->next = cur->next;
            cur = cur->next;
            free(tmp);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}

Node* encontrar_intersecao(Node *l1, Node *l2) {
    int c1 = contar_nos(l1), c2 = contar_nos(l2);
    while (c1 > c2) {
        l1 = l1->next;
        c1--;
    }
    while (c2 > c1) {
        l2 = l2->next;
        c2--;
    }
    while (l1 && l2) {
        if (l1 == l2) return l1;
        l1 = l1->next;
        l2 = l2->next;
    }
    return NULL;
}

void rotacionar_lista(Node **head, int k) {
    if (!*head || k == 0) return;
    Node *cur = *head;
    int len = 1;
    while (cur->next) {
        cur = cur->next;
        len++;
    }
    k = k % len;
    if (k == 0) return;
    cur->next = *head;
    Node *temp = *head;
    int i;
    for (i = 0; i < len - k - 1; i++) temp = temp->next;
    *head = temp->next;
    temp->next = NULL;
}

typedef struct MinStackNode {
    int val;
    int min;
    struct MinStackNode *next;
} MinStackNode;

typedef struct {
    MinStackNode *top;
} MinStack;

void minstack_push(MinStack *s, int val) {
    MinStackNode *n = malloc(sizeof(MinStackNode));
    n->val = val;
    n->min = (!s->top || val < s->top->min) ? val : s->top->min;
    n->next = s->top;
    s->top = n;
}

void minstack_pop(MinStack *s) {
    if (s->top) {
        MinStackNode *tmp = s->top;
        s->top = s->top->next;
        free(tmp);
    }
}

int minstack_top(MinStack *s) {
    if (!s->top) return -1;
    return s->top->val;
}

int minstack_get_min(MinStack *s) {
    if (!s->top) return -1;
    return s->top->min;
}

typedef struct {
    int data[100];
    int top1, top2;
} DuasPilhas;

void duaspilhas_init(DuasPilhas *p) {
    p->top1 = -1;
    p->top2 = 100;
}

void push1(DuasPilhas *p, int val) {
    if (p->top1 + 1 == p->top2) return;
    p->data[++(p->top1)] = val;
}

void push2(DuasPilhas *p, int val) {
    if (p->top1 + 1 == p->top2) return;
    p->data[--(p->top2)] = val;
}

int pop1(DuasPilhas *p) {
    if (p->top1 == -1) return -1;
    return p->data[(p->top1)--];
}

int pop2(DuasPilhas *p) {
    if (p->top2 == 100) return -1;
    return p->data[(p->top2)++];
}

int avaliar_posfixa(char *expr) {
    Pilha p = {.top = -1};
    char *token = strtok(expr, " ");
    while (token) {
        if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            int b = pop(&p);
            int a = pop(&p);
            int res = 0;
            switch(token[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            push(&p, res);
        } else {
            push(&p, atoi(token));
        }
        token = strtok(NULL, " ");
    }
    return pop(&p);
}

typedef struct {
    Pilha s1, s2;
} FilaDuasPilhas;

void fila2pilhas_init(FilaDuasPilhas *f) {
    f->s1.top = -1;
    f->s2.top = -1;
}

void fila2pilhas_enfileirar(FilaDuasPilhas *f, int val) {
    push(&f->s1, val);
}

int fila2pilhas_desenfileirar(FilaDuasPilhas *f) {
    if (esta_vazia(&f->s2)) {
        while (!esta_vazia(&f->s1)) push(&f->s2, pop(&f->s1));
    }
    return pop(&f->s2);
}

int fila2pilhas_frente(FilaDuasPilhas *f) {
    if (esta_vazia(&f->s2)) {
        while (!esta_vazia(&f->s1)) push(&f->s2, pop(&f->s1));
    }
    return topo(&f->s2);
}

void inverter_grupos(Node **head, int k) {
    if (!*head || k <= 1) return;
    Node dummy; dummy.next = *head;
    Node *prev = &dummy, *cur = *head, *nex;
    int count;
    while (1) {
        Node *temp = cur;
        count = 0;
        while (temp && count < k) {
            temp = temp->next;
            count++;
        }
        if (count < k) break;
        Node *start = cur, *end = cur;
        Node *prev_sub = NULL;
        int i;
        for (i = 0; i < k; i++) {
            nex = cur->next;
            cur->next = prev_sub;
            prev_sub = cur;
            cur = nex;
        }
        prev->next = prev_sub;
        start->next = cur;
        prev = start;
    }
    *head = dummy.next;
}

int eh_palindromo(Node *head) {
    if (!head || !head->next) return 1;
    Node *slow = head, *fast = head, *prev = NULL, *tmp;
    
    // Inverte a primeira metade enquanto avança slow e fast
    while (fast && fast->next) {
        fast = fast->next->next;
        tmp = slow;
        slow = slow->next;
        tmp->next = prev;
        prev = tmp;
    }
    
    Node *left = prev;
    Node *right = (fast) ? slow->next : slow;  // Se fast != NULL, lista ímpar, pula o meio
    
    int res = 1;
    // Compara as duas metades
    while (left && right) {
        if (left->val != right->val) {
            res = 0;
            break;
        }
        left = left->next;
        right = right->next;
    }
    
    // Restaura a lista original (inverte a primeira metade novamente)
    Node *cur = prev, *next = NULL, *prev2 = NULL;
    while (cur) {
        next = cur->next;
        cur->next = prev2;
        prev2 = cur;
        cur = next;
    }
    if (fast) slow->next = prev2;
    else if (prev2) {
        Node *tmp2 = prev2;
        while (tmp2->next) tmp2 = tmp2->next;
        tmp2->next = slow;
    }
    return res;
}
int main() {
    // Testando lista ligada
    Node *lista = NULL;
    inserir_fim(&lista, 10);
    inserir_fim(&lista, 20);
    inserir_fim(&lista, 30);
    inserir_inicio(&lista, 5);
    printf("Lista original: ");
    Node *cur;
    for (cur = lista; cur; cur = cur->next) {
        printf("%d ", cur->val);
    }
    printf("\n");

    inverter_lista(&lista);
    printf("Lista invertida: ");
    for (cur = lista; cur; cur = cur->next) {
        printf("%d ", cur->val);
    }
    printf("\n");

    // Testando pilha estática
    Pilha p = {.top = -1};
    push(&p, 1);
    push(&p, 2);
    push(&p, 3);
    printf("Pilha: ");
    while (!esta_vazia(&p)) {
        printf("%d ", pop(&p));
    }
    printf("\n");

    // Testando verificar balanceamento de parênteses
    char expr1[] = "{[()]}";
    char expr2[] = "{[(])}";
    printf("Expressao '%s' esta balanceada? %s\n", expr1, verificar_balanceamento(expr1) ? "Sim" : "Nao");
    printf("Expressao '%s' esta balanceada? %s\n", expr2, verificar_balanceamento(expr2) ? "Sim" : "Nao");

    // Testando fila com array
    FilaArr f;
    inicializar_fila(&f);
    enfileirar(&f, 100);
    enfileirar(&f, 200);
    enfileirar(&f, 300);
    printf("Fila: ");
    while (f.size > 0) {
        printf("%d ", desenfileirar(&f));
    }
    printf("\n");

    return 0;
}
