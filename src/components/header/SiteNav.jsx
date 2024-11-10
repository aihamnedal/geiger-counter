// components/header/SiteNav.jsx
import React, { useEffect } from 'react';
import { Link } from 'react-scroll';  // Import Link from react-scroll
import logo from '../../assets/brand-logo.png';  // Import your logo image

function SiteNav() {
  useEffect(() => {
    const handleScroll = () => {
      const navbar = document.querySelector('.navbar');
      if (window.scrollY > 0) {
        navbar.classList.add('scrolled');
      } else {
        navbar.classList.remove('scrolled');
      }
    };

    window.addEventListener('scroll', handleScroll);

    // Cleanup the event listener on component unmount
    return () => {
      window.removeEventListener('scroll', handleScroll);
    };
  }, []);

  return (
    <nav className="navbar navbar-expand-lg navbar-dark" style={{ backgroundColor: '#212121', position: 'fixed', top: '0', left: '0', right: '0', zIndex: '1000', boxShadow: '0 4px 6px rgba(0, 0, 0, 0.1)' }}>
      <div className="container-fluid">
        {/* Logo with Image */}
        <a className="navbar-brand" href="#" style={{ paddingLeft: '20px' }}>
          <img src={logo} alt="Gamma Sense Logo" style={{ height: '40px', width: 'auto' }} />
        </a>
        <button className="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
          <span className="navbar-toggler-icon"></span>
        </button>
        <div className="collapse navbar-collapse" id="navbarNav">
          <ul className="navbar-nav" style={{ marginLeft: '35%', display: 'flex', justifyContent: 'center', gap: '20px' }}>
            <li className="nav-item">
              <Link 
                to="home-section" 
                smooth={true}
                duration={500} 
                className="nav-link hover-effect">
                Home
              </Link>
            </li>
            <li className="nav-item">
              <Link 
                to="devices-section" 
                smooth={true} 
                duration={500} 
                className="nav-link hover-effect">
                Devices
              </Link>
            </li>
            <li className="nav-item">
              <Link 
                to="visualize-section" 
                smooth={true} 
                duration={500} 
                className="nav-link hover-effect">
                Visualize
              </Link>
            </li>
            <li className="nav-item">
              <Link 
                to="analyze-section" 
                smooth={true} 
                duration={500} 
                className="nav-link hover-effect">
                Analyze
              </Link>
            </li>
          </ul>
        </div>
      </div>
    </nav>
  );
}

export default SiteNav;
