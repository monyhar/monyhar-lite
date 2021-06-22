
import webbrowser

def main():
    try:
        webbrowser.open('https://so.monyhar.top/', new=2, autoraise=True)
    except:
        print('Failed connect to the Internet!')
    else:
        print('Successfully connect to the Internet!')

if __name__ == "__main__":
    main()
