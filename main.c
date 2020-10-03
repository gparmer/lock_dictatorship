#define LOCK_COARSE              1 /* The dictator is well and maintaining global order! */
//#define DEEPSTATE_LOCK_PHASEI_SEQUENTIAL_TAKES   1
//#define DEEPSTATE_LOCK_PHASEII_HAND_OVER_HAND    1

#define WORKER_WORK            (32)
#define WRITER_WORK            WORKER_WORK
#define PERSONAL_TIME          10
//#define DEEPSTATE_LOCK_2NDFRONT_RW                1

#define _GNU_SOURCE
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

struct freedom_node {
	int ma_freedoms;	/* We provide infinite freedom (modula 2^32)! */
#ifdef DEEPSTATE_LOCK_2NDFRONT_RW
#else
	pthread_mutex_t lock;
#endif	/* DEEPSTATE_LOCK_2NDFRONT_RW */
	struct freedom_node *next;
};

struct freedom_node head;

/*
 * Our lock options. Broken down into `read_` and `write_`
 * variants. Note that without phase IV of the coup, the read and
 * write variants are the same (thus some good-old-fashioned
 * doublespeak).
 */
void
read_lock(struct freedom_node *n)
{
#ifdef DEEPSTATE_LOCK_2NDFRONT_RW
#else
	pthread_mutex_lock(&n->lock);
#endif	/* DEEPSTATE_LOCK_2NDFRONT_RW */
}

void
write_lock(struct freedom_node *n)
{
#ifdef DEEPSTATE_LOCK_2NDFRONT_RW
#else
	read_lock(n);		/* 1984 style doublespeak */
#endif	/* DEEPSTATE_LOCK_2NDFRONT_RW */
}

void
read_unlock(struct freedom_node *n)
{
#ifdef DEEPSTATE_LOCK_2NDFRONT_RW
#else
	pthread_mutex_unlock(&n->lock);
#endif	/* DEEPSTATE_LOCK_2NDFRONT_RW */
}

void
write_unlock(struct freedom_node *n)
{
#ifdef DEEPSTATE_LOCK_2NDFRONT_RW
#else
	read_unlock(n);		/* 1984 style doublespeak */
#endif	/* DEEPSTATE_LOCK_2NDFRONT_RW */
}

void
personal_time(void)
{
	usleep(PERSONAL_TIME);
}

/* Allocate a new, free citizen-node. */
struct freedom_node *
create_freedom(void)
{
	struct freedom_node *n = malloc(sizeof(struct freedom_node));

	if (!n) return NULL;
#ifdef DEEPSTATE_LOCK_2NDFRONT_RW
#else
	pthread_mutex_init(&n->lock, NULL);
#endif	/* DEEPSTATE_LOCK_2NDFRONT_RW */

	n->ma_freedoms = 1;

	return n;
}

/* Simply add a new citizen-node to the list to increase cohesive freedom */
void
add_freedoms(void)
{
	struct freedom_node *n = create_freedom();

	/* PUSH logic */
	assert(n);

 	write_lock(&head);
	n->next   = head.next;
	head.next = n;
	write_unlock(&head);

	return;
}

/*
 * Time to "protect" your freedoms! We've identified an unpatriotic
 * node-citizen. Time to remove them from the list for "re-education".
 */
void
protect_freedoms(void)
{
	struct freedom_node *n;

	/* POP logic */
	write_lock(&head);
	n = head.next;
	if (!n) {
		write_unlock(&head); /* this necessary operation is *REALLY* easy to forget */
		return;
	}
	write_lock(n);
	head.next = n->next;
	write_unlock(n);
	write_unlock(&head);

	pthread_mutex_destroy(&n->lock);
	free(n);

	return;
}

volatile int work = 0, ensuring_freedoms = 1;

/* Yeah, you gotta workworkworkworkwork... */
void
work_work(struct freedom_node *n)
{
	int i;
	(void)n;
	printf("r");

	/* https://www.youtube.com/watch?v=RP4cD35Xn5E */
	for (i = 0; i < WORKER_WORK; i++) work++;
}

void
moar_freedoms(struct freedom_node *n)
{
	int i;
	printf("w");

	n->ma_freedoms++;
	for (i = 0; i < WRITER_WORK; i++) work++;
}

#define ITER 16

void *
freedom_police(void *d)
{
	/* current and previous node */
	struct freedom_node *current_node, *prev_node;
	int i, j;
	(void)d;

	for (i = 0; i < ITER; i++) {
		for (j = 0; j < 128; j++) add_freedoms();

		current_node = &head;
		prev_node    = NULL;

		/*
		 * This is messy, but only one of the ifdef blocks
		 * should be active at any point in time, so ignore
		 * the others.
		 */
#ifdef  LOCK_COARSE
		write_lock(&head);
		while (current_node) {
			moar_freedoms(current_node);
			current_node = current_node->next;
		}
		write_unlock(&head);
#endif	/*  LOCK_COARSE */

#ifdef DEEPSTATE_LOCK_PHASEI_SEQUENTIAL_TAKES
		while (current_node) {
			write_lock(current_node);
			moar_freedoms(current_node);
			prev_node    = current_node;
			current_node = current_node->next;
			write_unlock(prev_node);
		}
#endif	/* DEEPSTATE_LOCK_PHASEI_SEQUENTIAL_TAKES */

#ifdef DEEPSTATE_LOCK_PHASEII_HAND_OVER_HAND
		write_lock(current_node);
		while (current_node) {
			moar_freedoms(current_node);
			prev_node    = current_node;
			current_node = current_node->next;
			if (current_node) write_lock(current_node);
			write_unlock(prev_node);
		}
#endif	/* DEEPSTATE_LOCK_PHASEII_HAND_OVER_HAND */
		personal_time();
		for (j = 0; j < 128; j++) protect_freedoms();
	}

	ensuring_freedoms = 0;

	return NULL;
}

void *
worker_patriot(void *d)
{
	(void)d;

	while (ensuring_freedoms) {
		/* current and previous node */
		struct freedom_node *current_node, *prev_node;

		current_node = &head;
		prev_node    = NULL;

		/*
		 * This is messy, but only one of the ifdef blocks
		 * should be active at any point in time, so ignore
		 * the others.
		 */
#ifdef  LOCK_COARSE
		read_lock(&head);
		while (current_node) {
			work_work(current_node);
			current_node = current_node->next;
		}
		read_unlock(&head);
#endif	/* LOCK_COARSE */

#ifdef DEEPSTATE_LOCK_PHASEI_SEQUENTIAL_TAKES
		while (current_node) {
			read_lock(current_node);
			work_work(current_node);
			prev_node    = current_node;
			current_node = current_node->next;
			read_unlock(prev_node);
		}
#endif	/* DEEPSTATE_LOCK_PHASEI_SEQUENTIAL_TAKES */

#ifdef DEEPSTATE_LOCK_PHASEII_HAND_OVER_HAND
		read_lock(current_node);
		while (current_node) {
			work_work(current_node);
			prev_node    = current_node;
			current_node = current_node->next;
			if (current_node) read_lock(current_node);
			read_unlock(prev_node);
		}
#endif	/* DEEPSTATE_LOCK_PHASEII_HAND_OVER_HAND */
		personal_time();
	}

	return NULL;
}

void
panic(char *msg)
{
	if (errno) perror(msg);
	else       printf("%s", msg);
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	pthread_t updater, worker1, worker2;
	int i;
	(void)argc; (void)argv;

	head.next = NULL;
	pthread_mutex_init(&head.lock, NULL);
	for (i = 0; i < 1024; i++) {
		add_freedoms();
	}

	if (pthread_create(&updater, NULL, freedom_police, NULL)) panic("pthread_create");
	if (pthread_create(&worker1, NULL, worker_patriot, NULL)) panic("pthread_create");
	if (pthread_create(&worker2, NULL, worker_patriot, NULL)) panic("pthread_create");
	pthread_join(updater, NULL);
	pthread_join(worker1, NULL);
	pthread_join(worker2, NULL);

	for (i = 0; i < 1024; i++) {
		protect_freedoms();
	}
	pthread_mutex_destroy(&head.lock);

	printf("\nThe great leader is strong! Mutual exclusion for all!\n");

	return 0;
}
