def main():
    initial_position = float(input("Enter initial position: "))
    initial_velocity = float(input("Enter initial velocity: "))
    acceleration = float(input("Enter acceleration: "))
    time = float(input("Enter time for project: "))
    
    final_position = calculate_final_position(initial_position, initial_velocity, acceleration, time)
    
    print("Final position:", final_position)

def calculate_final_position(initial_position, initial_velocity, acceleration, time):
    final_position = initial_position + initial_velocity * time + 0.5 * acceleration * time ** 2
    return final_position

if __name__ == "__main__":
    main()
