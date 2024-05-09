#Python script to count meals from the output file and append the result

def count_meals_and_append(file_path):
    with open(file_path, 'r+') as file:
        log_entries = file.read()
        meal_counts = {}
        for line in log_entries.strip().split('\n'):
            parts = line.split()
            if len(parts) == 4 and parts[2] == "is" and parts[3] == "eating":
                philosopher_id = int(parts[1])
                meal_counts[philosopher_id] = meal_counts.get(philosopher_id, 0) + 1

        # Append the meal counts to the file
        file.write("\nMeal counts per philosopher:\n")
        for philosopher_id, count in meal_counts.items():
            file.write(f"Philosopher {philosopher_id} ate {count} times\n")

#Replace 'output.txt' with the path to your output file
count_meals_and_append('output.txt')
