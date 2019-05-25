import random
import subprocess

def random_string():
    letters  ="abcdefgh"
    k = random.randint(1, 5)
    s = ""
    for i in range(k):
        s += random.choice(letters)

    return s

def random_strings():
    k = random.randint(1, 25)
    return list(set(random_string() for s in range(k)))


def main():
    print("Testing Trie iteration protocol")
    for i in range(10):
        strings = random_strings()
        answer = set(strings)
        try:
            output = subprocess.check_output(["./bin/itertrie"] + strings)
        except subprocess.CalledProcessError:
            print("Process failed on input")
            print(*strings, sep="\n")
            break
        
        output = output.decode()
        lines = set(l.strip() for l in output.split("\n") if l.strip())

        if lines != answer:
            print("Actual:")
            print(*answer, sep="\n", end="\n\n")
            print("Got:")
            print(*lines, sep="\n", end="\n\n")
            break
        
        print("Test", i, "ok")
    
    print()


if __name__ == "__main__":
    main()