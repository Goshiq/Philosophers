ONE		= philo_one

TWO		= philo_two

THREE	= philo_three

all:
		cd ./$(ONE) && make
		cd ./$(TWO) && make
		cd ./$(THREE) && make

clean:
		cd ./$(ONE) && make clean
		cd ./$(TWO) && make clean
		cd ./$(THREE) && make clean

fclean:
		cd ./$(ONE) && make fclean
		cd ./$(TWO) && make fclean
		cd ./$(THREE) && make fclean

re:
		cd ./$(ONE) && make re
		cd ./$(TWO) && make re
		cd ./$(THREE) && make re

.PHONY:	all clean fclean re
