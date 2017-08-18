
typedef uint16 rgb15;

struct s_scoreboard
{
	volatile obj_attrs *first_digit;
	volatile obj_attrs *second_digit;
};

typedef struct s_scoreboard t_scoreboard;

// Form a 16-bit BGR GBA colour from three component values
static inline rgb15 RGB15(int r, int g, int b)
{
	return r | (g << 5) | (b << 10);
}
