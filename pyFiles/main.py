import serial
import os
import spotipy
from dotenv import load_dotenv

load_dotenv()

CLIENT_ID = os.getenv("CLIENT_ID")
CLIENT_SECRET = os.getenv("CLIENT_SECRET")
DEVICE_ID = os.getenv("DEVICE_ID")

IR_BUTTON_FASTFW = "67"
IR_BUTTON_REWIND = "68"
IR_BUTTON_PLAY_PAUSE = "64"


def send_song_name(sp, ser):
    name = sp.current_user_playing_track()["item"]["name"]
    name = name.encode("utf-8")
    ser.write(name)

if __name__ == "__main__":
    sp = spotipy.Spotify(
        auth_manager=spotipy.SpotifyOAuth(
            scope="user-read-playback-state user-modify-playback-state user-library-read"
        )
    )
    ser = serial.Serial("COM3", baudrate=9600, timeout=1)
  
    try:
        print("Arduino Starting...")
        while True:
            try:
                data = ser.readline().decode("utf-8").strip()
                if data == IR_BUTTON_FASTFW:
                    print("skipping track")
                    sp.next_track()
                    send_song_name(sp, ser)

                elif data == IR_BUTTON_REWIND:
                    print("go to previous track")
                    sp.previous_track()
                    send_song_name(sp, ser)

                elif data == IR_BUTTON_PLAY_PAUSE:
                    current_playback = sp.current_playback()
                    if current_playback["is_playing"] == False:
                        sp.start_playback()
                        msg = "Resume playing".encode("utf-8")
                        ser.write(msg)
                    elif current_playback["is_playing"] == True:
                        sp.pause_playback(device_id=DEVICE_ID)
                        msg = "Paused playing".encode("utf-8")
                        ser.write(msg)
                elif data != "":
                    print("NO MATCH:", data)
            except spotipy.SpotifyException:
                pass

    except KeyboardInterrupt:
        ser.close()
        print("serial connection closed")
    