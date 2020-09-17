#include "pintos_thread.h"

struct station {
	struct lock *lock;
	struct condition *cond; 
	int total_passengers;
	int total_seats;
};

void
station_init(struct station *station)
{
	station->total_passengers = 0;
	station->total_seats = 0;
	lock_init(station->lock);
	cond_init(station->cond);
}

void
station_load_train(struct station *station, int count)
{
	lock_acquire(station->lock);
	station->total_seats = count;
	lock_release(station->lock);
	cond_broadcast(station->cond, station->lock);
}

void
station_wait_for_train(struct station *station)
{
	lock_acquire(station->lock);
	station->total_passengers++;
	while (!station->total_seats)
		cond_wait(station->cond, station->lock);
	station->total_seats--;
	lock_release(station->lock);
}

void
station_on_board(struct station *station)
{
	// FILL ME IN
}
