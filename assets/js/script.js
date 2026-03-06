// Select all navbar buttons and all sections
const navLinks = document.querySelectorAll('.navbar-link');
const sections = document.querySelectorAll('section');

// Function to show the section corresponding to the clicked button
navLinks.forEach((link, index) => {
  link.addEventListener('click', () => {
    // Remove 'active' from all sections
    sections.forEach(sec => sec.style.display = 'none');
    // Remove 'active' from all buttons
    navLinks.forEach(btn => btn.classList.remove('active'));

    // Show the selected section
    sections[index].style.display = 'block';
    link.classList.add('active');
  });
});

// Initialize: show first section only
sections.forEach((sec, i) => {
  sec.style.display = i === 0 ? 'block' : 'none';
});
