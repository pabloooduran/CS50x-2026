document.addEventListener("DOMContentLoaded", function () {
    const welcomeBtn = document.querySelector("#welcome-btn");
    const welcomeText = document.querySelector("#welcome-text");

    if (welcomeBtn) {
        welcomeBtn.addEventListener("click", function () {
            welcomeText.textContent = "Thanks for visiting my homepage. I hope you enjoy exploring it.";
        });
    }

    const factBtn = document.querySelector("#fact-btn");
    const factText = document.querySelector("#fact-text");
    const facts = [
        "I enjoy active routines and staying in motion.",
        "Sports help me feel focused, motivated, and disciplined.",
        "I like challenges that help me improve little by little.",
        "Consistency is one of the values I admire most."
    ];

    if (factBtn) {
        factBtn.addEventListener("click", function () {
            const randomIndex = Math.floor(Math.random() * facts.length);
            factText.textContent = facts[randomIndex];
        });
    }

    const moodSelect = document.querySelector("#mood-select");
    const moodResult = document.querySelector("#mood-result");

    if (moodSelect) {
        moodSelect.addEventListener("change", function () {
            if (moodSelect.value === "focused") {
                moodResult.textContent = "That sounds great. A focused mindset is perfect for progress.";
            } else if (moodSelect.value === "energetic") {
                moodResult.textContent = "Amazing. High energy is ideal for training and getting things done.";
            } else if (moodSelect.value === "relaxed") {
                moodResult.textContent = "Nice. A calm mind can be just as powerful as a busy one.";
            } else {
                moodResult.textContent = "";
            }
        });
    }

    const sportButtons = document.querySelectorAll(".sport-btn");
    const sportResult = document.querySelector("#sport-result");

    if (sportButtons.length > 0) {
        sportButtons.forEach(function (button) {
            button.addEventListener("click", function () {
                sportResult.textContent = button.dataset.message;
            });
        });
    }

    const contactForm = document.querySelector("#contact-form");
    const formResult = document.querySelector("#form-result");

    if (contactForm) {
        contactForm.addEventListener("submit", function (event) {
            event.preventDefault();

            const name = document.querySelector("#name").value.trim();
            const message = document.querySelector("#message").value.trim();

            if (name === "" || message === "") {
                formResult.textContent = "Please complete both fields before sending the form.";
                formResult.style.color = "#c62828";
            } else {
                formResult.textContent = "Thanks, " + name + "! Your message has been sent successfully.";
                formResult.style.color = "#16783c";
            }
        });
    }
});
