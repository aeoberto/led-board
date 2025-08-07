# led-board
Desk-mounted LED device to show user status (Available, Busy, Away) in open office environments.

# Arduino
To connect and control the display of the LED boards, we used the Arduino IDE. To connect to the boards, first navigate to the preferences and paste "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json" into the additional boards manager URLs. Afterwards, navigate to Tools > Boards > ESP32 and select "Adafruit MatrixPortal ESP32-S3". Then plug in your board and select the correct port. Additionally, in the boards manager search for and download "Arduino ESP32 Boards". Lastly, download the Adafruit Protomatter library. 

# AWS
Create a Node.js lighstail instance.

# Server
In this instance, we used Node.js to handle HTTP requests to and from the instance. 
To ensure the server is always running, install pm2 using the instructions found here https://pm2.io/docs/runtime/guide/installation/.
Additionally, install MySQL12 to connect to the database.
```
npm i mysql2
```
In the JavaScript file, add


# Database
To store user information, we used MariaDB. Run these commands in the Lightsail instance and create a user that is accessible from our server. 

**Update packages and install mariadb**
```
sudo apt update -y
sudo apt install mariadb-server -y
```
**Start and enable the database**
```
sudo systemctl start mariadb
sudo systemctl enable mariadb
```
**Secure MariaDB (you will be given mulitple prompts, it is best to enter Y for all of them)**
```
sudo mysql_secure_installation
```
**Create a new user**
```
sudo mysql -u root
CREATE USER 'myuser'@'localhost' IDENTIFIED BY 'mypassword';
GRANT ALL PRIVILEGES ON *.* TO 'myuser'@'localhost' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EXIT;
```
**Now, after creating your database, add this to the JavaScript file**
```Javascript
const connection = mysql.createConnection({
  host:'localhost',
  user:'myuser',
  password:'mypassword',
  database:'users',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
})
```
# Python
For user interaction, we used Python along with PyInstaller to make executable files that the user can use to change the text on their boards. 
**First, install the tabulate library**
```
pip install tabulate
```
**Now install PyInstaller**
```
pip install -U pyinstaller
```
