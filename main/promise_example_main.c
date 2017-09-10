/* Promise Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>

// start library *****************************

typedef struct promise_t {
    void (*callback)(void *);
    char *resolve;
    char *reject;
    int success;
} promise;

// store the callback for usage later
void promise_new(promise *pr, void (*callback)(void *)) {
    printf("promise_new()\n");
    pr->callback = callback;
    pr->success = 0;
}

// store the resolution result
void promise_resolve(promise *pr, char *result) {
    printf("promise_resolve()\n");
    pr->resolve = result;
    pr->success = 1;
}

// store the rejection result
void promise_reject(promise *pr, char *reject) {
    printf("promise_reject()\n");
    pr->reject = reject;
}

// execute the call back, then execute the correct function depending on the callback result
void promise_then(promise *pr, void (*result_fn)(promise *), void (*err_fn)(promise *)) {
    printf("promise_then()\n");
    pr->callback(pr);
    if (pr->success) {
        result_fn(pr);
    } else {
        err_fn(pr);
    }
}

// end library *******************************

void callback(void *pr_ptr) {
    printf("callback()\n");
    promise *pr = pr_ptr;
    // do something, possibly async?

    if (1) {
        promise_resolve(pr, "Stuff worked!\n");
    } else {
        promise_reject(pr, "Does not break. It broke.\n");
    }
}

void result_fn(promise *pr) {
    printf("result_fn()\n");
    printf(pr->resolve);
}

void err_fn(promise *pr) {
    printf("err_fn()\n");
    printf(pr->reject);
}

void app_main()
{
    printf("Started example\n");
    
    promise pr;
    promise_new(&pr, callback);

    promise another;
    another = promise_then(&pr, result_fn, err_fn);
}
