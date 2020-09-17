#include "pintos_thread.h"

// Forward declaration. This function is implemented in reaction-runner.c,
// but you needn't care what it does. Just be sure it's called when
// appropriate within reaction_o()/reaction_h().
void make_water();

struct reaction {
	struct lock lock;
	struct condition cond_o;
	struct condition cond_h2o;
	int total_h;
};

void
reaction_init(struct reaction *reaction)
{
	lock_init(&reaction->lock);
	cond_init(&reaction->cond_o);
	cond_init(&reaction->cond_h2o);
	reaction->total_h = 0;
}

void
reaction_h(struct reaction *reaction)
{
	lock_acquire(&reaction->lock);
	reaction->total_h++;
	cond_signal(&reaction->cond_o, &reaction->lock);
	cond_wait(&reaction->cond_h2o, &reaction->lock);

	lock_release(&reaction->lock);
}

void
reaction_o(struct reaction *reaction)
{
	lock_acquire(&reaction->lock);
	while (reaction->total_h < 2) {
		cond_wait(&reaction->cond_o, &reaction->lock);
	}
	reaction->total_h -= 2;
	cond_signal(&reaction->cond_h2o, &reaction->lock);
	cond_signal(&reaction->cond_h2o, &reaction->lock);
	make_water();
	lock_release(&reaction->lock);
	// lock_acquire(&reaction->lock);
	// reaction->total_o++;
	// if (reaction->total_h >= 2) {
	// 	cond_signal(&reaction->cond_1h_wait, &reaction->lock);
	// 	cond_signal(&reaction->cond_2h_wait, &reaction->lock);

	// } else {
	// 	while (reaction->total_h < 2) 
	// 		cond_wait(&reaction->cond_o_wait, &reaction->lock);
	// }
	// make_water();
	// printf("h: %d\n", reaction->total_o);
	// reaction->total_o--;
	// lock_release(&reaction->lock);	
}
