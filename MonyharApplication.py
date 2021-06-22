
import webbrowser

def main():
    try:
        webbrowser.open('https://so.monyhar.top/', new=2, autoraise=True)
    except:
        print('Failed connect to the Internet!')
        print('Start retrying now...')
        main()
    else:
        print('Successfully connect to the Internet!')
    
if __name__ == "__main__":
    main()
