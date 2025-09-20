NAME      := philo
CC        := cc
CFLAGS    := -Wall -Wextra -Werror -O2 -pipe
CPPFLAGS  := -Iinclude
LDLIBS    := -pthread

SRCDIR    := src
BUILDDIR  := build
SRCS      := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/init/*.c) $(wildcard $(SRCDIR)/utils/*.c) $(wildcard $(SRCDIR)/action/*.c) $(wildcard $(SRCDIR)/core/*.c)
OBJS      := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS      := $(OBJS:.o=.d)

GREEN     := \033[32m
CYAN      := \033[36m
YELLOW    := \033[33m
RED       := \033[31m
WHITE     := \033[37m
BOLD      := \033[1m
RESET     := \033[0m

# Bleu plus pur (moins de rouge, plus de bleu)
MAJORELLE := \033[38;2;50;100;255m

define ASCII_ART
$(MAJORELLE)
░▒█▀▀█░▒█░▒█░▀█▀░▒█░░░░▒█▀▀▀█░▒█▀▀▀█░▒█▀▀▀█░▒█▀▀█░▒█░▒█░▒█▀▀▀░▒█▀▀▄
░▒█▄▄█░▒█▀▀█░▒█░░▒█░░░░▒█░░▒█░░▀▀▀▄▄░▒█░░▒█░▒█▄▄█░▒█▀▀█░▒█▀▀▀░▒█▄▄▀
░▒█░░░░▒█░▒█░▄█▄░▒█▄▄█░▒█▄▄▄█░▒█▄▄▄█░▒█▄▄▄█░▒█░░░░▒█░▒█░▒█▄▄▄░▒█░▒█
$(RESET)
endef
export ASCII_ART

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all clean fclean re run quiz

# Quiz technique difficile
quiz:
	@echo ""
	@printf "$(GREEN)[Début du Quiz]$(RESET)\n"
	@echo ""
	@printf "$(MAJORELLE)Question 1: Qui a inventé le problème des dining philosophers ?$(RESET)\n"
	@echo ""
	@printf "$(MAJORELLE)[1]$(RESET) Alan Turing\n"
	@printf "$(MAJORELLE)[2]$(RESET) Edsger Dijkstra\n"
	@printf "$(MAJORELLE)[3]$(RESET) Linus Torvalds\n"
	@printf "$(MAJORELLE)[4]$(RESET) Richard Stallman\n"
	@echo ""
	@read -p "Votre réponse (1-4): " answer1; \
	if [ "$$answer1" = "2" ]; then \
		printf "$(GREEN)🎯 Excellent ! Dijkstra a créé ce problème classique en 1965 !$(RESET)\n"; \
		score=1; \
	else \
		printf "$(RED)💀 Échec ! C'était Edsger Dijkstra !$(RESET)\n"; \
		score=0; \
	fi; \
	echo ""; \
	printf "$(MAJORELLE)Question 2: Qu'est-ce qu'un mutex ?$(RESET)\n"; \
	echo ""; \
	printf "$(MAJORELLE)[1]$(RESET) Un type de variable en C\n"; \
	printf "$(MAJORELLE)[2]$(RESET) Un mécanisme de synchronisation qui protège les ressources partagées\n"; \
	printf "$(MAJORELLE)[3]$(RESET) Une fonction de la libc\n"; \
	printf "$(MAJORELLE)[4]$(RESET) Un compilateur\n"; \
	echo ""; \
	read -p "Votre réponse (1-4): " answer2; \
	if [ "$$answer2" = "2" ]; then \
		printf "$(GREEN)🔒 Parfait ! Un mutex (mutual exclusion) protège les sections critiques !$(RESET)\n"; \
		score=$$((score + 1)); \
	else \
		printf "$(RED)💀 Échec ! C'est un mécanisme de synchronisation !$(RESET)\n"; \
	fi; \
	echo ""; \
	printf "$(MAJORELLE)Question 3: Quelle est la différence entre un thread et un processus ?$(RESET)\n"; \
	echo ""; \
	printf "$(MAJORELLE)[1]$(RESET) Aucune différence\n"; \
	printf "$(MAJORELLE)[2]$(RESET) Un thread partage la mémoire avec son processus parent, un processus a sa propre mémoire\n"; \
	printf "$(MAJORELLE)[3]$(RESET) Un thread est plus rapide qu'un processus\n"; \
	printf "$(MAJORELLE)[4]$(RESET) Un processus est plus rapide qu'un thread\n"; \
	echo ""; \
	read -p "Votre réponse (1-4): " answer3; \
	if [ "$$answer3" = "2" ]; then \
		printf "$(GREEN)🧠 Bravo ! Vous maîtrisez la concurrence !$(RESET)\n"; \
		score=$$((score + 1)); \
	else \
		printf "$(RED)💀 Échec ! Un thread partage la mémoire, un processus a sa propre mémoire !$(RESET)\n"; \
	fi; \
	echo ""; \
	if [ $$score -eq 3 ]; then \
		printf "$(GREEN)🏆 PARFAIT ! 3/3 ! Vous êtes un vrai expert !$(RESET)\n"; \
	elif [ $$score -eq 2 ]; then \
		printf "$(YELLOW)👍 Bien joué ! 2/3 ! Presque parfait !$(RESET)\n"; \
	elif [ $$score -eq 1 ]; then \
		printf "$(CYAN)😐 Pas mal ! 1/3 ! Encore un effort !$(RESET)\n"; \
	else \
		printf "$(RED)💀 Catastrophe ! 0/3 ! Relisez vos cours !$(RESET)\n"; \
	fi; \
	echo ""; \
	$(MAKE) $(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$$ASCII_ART"
	@echo ""
	@printf "$(MAJORELLE)"
	@for c in "[" "S" "U" "C" "C" "E" "S" "S" "]"; do \
		printf "%s" "$$c"; \
		sleep 0.05; \
	done
	@printf "$(RESET)"
	@printf "$(WHITE)"
	@for c in " " "B" "i" "n" "a" "r" "y" " " "$(NAME)" " " "b" "u" "i" "l" "t" "!"; do \
		printf "%s" "$$c"; \
		sleep 0.05; \
	done
	@printf "$(RESET)"
	@echo ""
	@echo ""

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
	@printf "$(MAJORELLE)[CC]$(RESET) %s\n" "$<"

$(BUILDDIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILDDIR)
	@printf "$(GREEN)[CLEAN]$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)[FCLEAN]$(RESET)\n"

re: fclean all

run: $(NAME)
	@./$(NAME) $(ARGS)

-include $(DEPS)