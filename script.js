function generateOTP() {
  const length = parseInt(document.getElementById("otpLength").value);
  const output = document.getElementById("otpOutput");

  if (length < 1 || length > 10) {
    output.innerText = "Please enter a length between 1 and 10.";
    return;
  }

  let digits = [...Array(10).keys()];
  for (let i = digits.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [digits[i], digits[j]] = [digits[j], digits[i]];
  }

  const otp = digits.slice(0, length).join("");
  output.innerText = `Your OTP : ${otp}`;
}
