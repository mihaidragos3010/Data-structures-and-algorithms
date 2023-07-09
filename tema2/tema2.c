//Mihai Dragos-Andrei Grupa312CB
#include "functiiStiveSiCozi.h"
typedef struct celulag {
  void *info;
  struct celulag *urm;
} TCelulaG, *TLG;

typedef struct Thread {
  int id;
  int timp_rulare;
} Thread;

typedef struct Task {
  int id;
  Thread thread;
  int prioritate;
  int timp_exec;
} Task;

TStiva *CrearePool(int N) {
  ASt s;
  int d = sizeof(Thread);
  s = InitS(d);
  int i;
  for (i = N - 1; i >= 0; i--) {
    Thread *thread;
    thread = malloc(sizeof(Thread));
    if (thread == NULL) printf("nu e bine\n");
    thread->id = i;
    Push((void *)s, (void *)thread);
  }
  return s;
}

TStiva *CreareStivaId(TStiva *s) {
  int d = sizeof(Thread);
  s = InitS(d);
  int i;
  for (i = 128; i >= 1; i--) {
    Push((void *)s, (void *)&i);
  }
  return s;
}

void afisareStiva(TStiva s) {
  ASt aux;
  int d = sizeof(Task);
  aux = InitS(d);
  Task task;
  while (s.vf != NULL) {
    Pop(&s, (void *)&task);
    printf("%d %d\n", task.prioritate, task.id);
    Push(aux, (void *)&task);
  }
  while (aux->vf != NULL) {
    Pop(aux, (void *)&task);
    Push(&s, (void *)&task);
  }
}

void swichTask(Task *task1, Task *task2) {
  Task *aux;
  aux = malloc(sizeof(Task));
  if (aux == NULL) printf("Nu s-a reusit alocarea");
  aux->id = task1->id;
  aux->prioritate = task1->prioritate;
  aux->thread = task1->thread;
  aux->timp_exec = task1->timp_exec;

  task1->id = task2->id;
  task1->prioritate = task2->prioritate;
  task1->thread = task2->thread;
  task1->timp_exec = task2->timp_exec;

  task2->id = aux->id;
  task2->prioritate = aux->prioritate;
  task2->thread = aux->thread;
  task2->timp_exec = aux->timp_exec;
}

void sortareStivaTask(TStiva *s) {
  TStiva *aux;
  Task task;
  int d = sizeof(Task);
  aux = InitS(d);
  while (s->vf != NULL) {
    if (aux->vf == NULL) {
      Pop(s, &task);
      Push(aux, &task);
    } else {
      Pop(s, &task);
      if (task.prioritate > ((Task *)aux->vf->info)->prioritate) {
        while (aux->vf != NULL) {
          Task task_aux;
          Pop(aux, &task_aux);
          Push(s, &task_aux);
        }
      } else if (task.prioritate == ((Task *)aux->vf->info)->prioritate &&
                 task.timp_exec < ((Task *)aux->vf->info)->timp_exec) {
        while (aux->vf != NULL) {
          Task task_aux;
          Pop(aux, &task_aux);
          Push(s, &task_aux);
        }
      } else if (task.prioritate == ((Task *)aux->vf->info)->prioritate &&
                 task.timp_exec == ((Task *)aux->vf->info)->timp_exec &&
                 task.id < ((Task *)aux->vf->info)->id) {
        while (aux->vf != NULL) {
          Task task_aux;
          Pop(aux, &task_aux);
          Push(s, &task_aux);
        }
      }

      Push(aux, &task);
    }
  }

  while (aux->vf != NULL) {
    Pop(aux, &task);
    Push(s, &task);
  }
}

void InserareCoadaOrdonat(TCoada *c, Task *task) {
  TCoada *aux;
  int d = sizeof(Task);
  Task task_aux;
  aux = InitC(d);
  int ok = 0;
  if (c->ic == NULL) {
    InserareC(c, task);
    return;
  }
  while (c->ic != NULL) {
    ExtragereC(c, &task_aux);
    if (task->prioritate > task_aux.prioritate) {
      InserareC(aux, task);
      InserareC(aux, &task_aux);
      ok = 1;
      break;
    } else {
      if (task->prioritate == task_aux.prioritate &&
          task->timp_exec < task_aux.timp_exec) {
        InserareC(aux, task);
        InserareC(aux, &task_aux);
        ok = 1;
        break;
      } else {
        if (task->prioritate == task_aux.prioritate &&
            task->timp_exec == task_aux.timp_exec &&
            task->timp_exec < task_aux.timp_exec) {
          InserareC(aux, task);
          InserareC(aux, &task_aux);
          ok = 1;
          break;
        }
      }
    }
    InserareC(aux, &task_aux);
  }

  if (aux->ic != NULL && c->ic == NULL && ok != 1) {
    InserareC(aux, task);
  } else {
    while (c->ic != NULL) {
      ExtragereC(c, &task_aux);
      InserareC(aux, &task_aux);
    }
  }
  while (aux->ic != NULL) {
    ExtragereC(aux, &task_aux);
    InserareC(c, &task_aux);
  }
}

void afisareCoada(TCoada c) {
  TCoada *aux;
  int d = sizeof(Task);
  aux = InitC(d);
  while (c.ic != NULL) {
    Task task;
    ExtragereC(&c, &task);
    printf("task %d = t:%d p:%d (%d)\n", task.id, task.timp_exec,
           task.prioritate, task.thread.id);
    InserareC(aux, &task);
  }
  while (aux->ic != NULL) {
    Task task;
    ExtragereC(aux, &task);
    InserareC(&c, &task);
  }
}

void afisareCoadaWaiting(TCoada c, FILE *o) {
  TCoada *aux;
  Task task;
  int d = sizeof(Task);
  aux = InitC(d);
  int ok = 0;
  fprintf(o, "====== Waiting queue =======\n");
  fprintf(o, "[");
  while (c.ic->urm != NULL) {
    if (ok == 0) {
      ExtragereC(&c, &task);
      fprintf(o, "(%d: priority = %d, remaining_time = %d)", task.id,
              task.prioritate, task.timp_exec);
      InserareC(aux, &task);
    }
    ExtragereC(&c, &task);
    fprintf(o, ",\n(%d: priority = %d, remaining_time = %d)", task.id,
            task.prioritate, task.timp_exec);
    InserareC(aux, &task);
    ok++;
  }
  ExtragereC(&c, &task);
  fprintf(o, ",\n(%d: priority = %d, remaining_time = %d)", task.id,
          task.prioritate, task.timp_exec);
  InserareC(aux, &task);
  fprintf(o, "]\n");
  while (aux->ic != NULL) {
    Task task;
    ExtragereC(aux, &task);
    InserareC(&c, &task);
  }
}

void get_task(TCoada waiting, TCoada running, TCoada finish, int id, FILE *o) {
  TCoada *aux;
  Task task;
  int d = sizeof(Task);
  aux = InitC(d);
  while (running.ic != NULL) {
    ExtragereC(&running, &task);
    if (task.id == id)
      fprintf(o, "Task %d is running (remaining_time = %d).\n", task.id,
              task.timp_exec);
    InserareC(aux, &task);
  }
  while (aux->ic != NULL) {
    ExtragereC(aux, &task);
    InserareC(&running, &task);
  }
  while (waiting.ic != NULL) {
    ExtragereC(&waiting, &task);
    if (task.id == id)
      fprintf(o, "Task %d is waiting (remaining_time = %d).\n", task.id,
              task.timp_exec);
    InserareC(aux, &task);
  }
  while (aux->ic != NULL) {
    ExtragereC(aux, &task);
    InserareC(&waiting, &task);
  }

  while (finish.ic != NULL) {
    ExtragereC(&finish, &task);
    if (task.id == id)
      fprintf(o, "Task %d is finished (remaining_time = %d).\n", task.id,
              task.timp_exec);
    InserareC(aux, &task);
  }
  while (aux->ic != NULL) {
    ExtragereC(aux, &task);
    InserareC(&finish, &task);
  }
}

void get_thread(TCoada waiting, TCoada running, TCoada finish, TStiva Pool,
                int id, FILE *o) {
  int rez = 0;
  ASt auxS;
  int dS = sizeof(Thread);
  auxS = InitS(dS);
  while (Pool.vf != NULL) {
    Thread thread;
    Pop(&Pool, (void *)&thread);
    if (thread.id == id) {
      fprintf(o, "Thread %d is idle.\n", thread.id);
      rez = 1;
    }
    Push(auxS, (void *)&thread);
  }
  while (auxS->vf != NULL) {
    Thread thread;
    Pop(auxS, (void *)&thread);
    Push(&Pool, (void *)&thread);
  }

  if (rez == 0) {
    TCoada *auxC;
    Task task;
    int dC = sizeof(Task);
    auxC = InitC(dC);
    while (running.ic != NULL) {
      ExtragereC(&running, &task);
      if (task.thread.id == id)
        fprintf(o, "Thread %d is running task %d (remaining_time= %d).\n",
                task.thread.id, task.id, task.timp_exec);
      InserareC(auxC, &task);
    }
    while (auxC->ic != NULL) {
      ExtragereC(auxC, &task);
      InserareC(&running, &task);
    }
  }
}

void CreareWRF(TCoada *waiting, TCoada *running, TCoada *finish) {
  int d = sizeof(Task);
  waiting->dime = d;
  waiting->ic = NULL;
  waiting->sf = NULL;

  running->dime = d;
  running->ic = NULL;
  running->sf = NULL;

  finish->dime = d;
  finish->ic = NULL;
  finish->sf = NULL;
}

void add_tasks(TCoada *waiting, int nr, int timp_exec, int prioritate,
               TStiva *Pool, TStiva *TaskId, FILE *o) {
  int i;
  for (i = nr; i >= 1; i--) {
    Task task;
    Pop(TaskId, &task.id);
    task.prioritate = prioritate;  // adaugare din striva de Id in coada waiting
    task.timp_exec = timp_exec;
    InserareCoadaOrdonat(waiting, &task);  // tebuie inserat ordonat
    fprintf(o, "Task created successfully : ID %d.\n", task.id);
  }
}
int main(int argc, char *argv[]) {
  FILE *i, *o;
  i = fopen(argv[1], "rt");
  o = fopen(argv[2], "wt");
  char *inst;
  inst = malloc(sizeof(char) * 20);
  if (inst == NULL) return -1;
  int timp_maxim, C, N;
  fscanf(i, "%d", &timp_maxim);
  fscanf(i, "%d", &C);
  N = C * 2;

  TStiva *Pool = CrearePool(N);  // Creare Stiva Pool

  TCoada waiting, running, finish;  // Creare Cozi Waitind/Runnig/Finished
  CreareWRF(&waiting, &running, &finish);

  TStiva *TaskId = NULL;
  TaskId = CreareStivaId(TaskId);

  while (fscanf(i, "%s", inst) !=
         EOF) {  // filtrarea comenilor pentru a le putea executa
    if (strcmp(inst, "add_tasks") == 0) {
      int nr, timp_exec, prioritate;
      fscanf(i, "%d", &nr);
      fscanf(i, "%d", &timp_exec);
      fscanf(i, "%d", &prioritate);
      add_tasks(&waiting, nr, timp_exec, prioritate, Pool, TaskId, o);
    }
    if (strcmp(inst, "get_task") == 0) {
      int id;
      fscanf(i, "%d", &id);
      get_task(waiting, running, finish, id, o);
    }

    if (strcmp(inst, "get_thread") == 0) {
      int id;
      fscanf(i, "%d", &id);
      get_thread(waiting, running, finish, *Pool, id, o);
    }

    if (strcmp(inst, "print") == 0) {
      fscanf(i, "%s", inst);
      if (strcmp(inst, "waiting") == 0) {
        afisareCoadaWaiting(waiting, o);
      }
      if (strcmp(inst, "running") == 0) {
        fprintf(o, "====== Running in parallel =======\n");
        fprintf(o, "[]\n");
      }
      if (strcmp(inst, "finished") == 0) {
        fprintf(o, "====== Finished queue =======\n");
        fprintf(o, "[]\n");
      }
    }

    if (strcmp(inst, "run") == 0) {
    }

    if (strcmp(inst, "finish") == 0) {
    }
  }

  return 0;
}