import React, { useState } from 'react';
import './style.css';
function RegistrationPage() {
  const [name, setName] = useState('');
  const [age, setAge] = useState('');
  const [gender, setGender] = useState('');
  const [orientation, setOrientation] = useState('');
  const [city, setCity] = useState('');
  const [bio, setBio] = useState('');
  const [error, setError] = useState('');
  const [selectedFile, setSelectedFile] = useState(null);

  const validateName = (inputName) => {
    if (/^[a-zA-Z]+$/.test(inputName) && inputName.length <= 20) {
      setError('');
      return true;
    } else {
      setError('Name only words');
      return false;
    }
  };

  const validateBio = (inputBio) => {
    if (inputBio.length <= 50) {
          setError(""); 
        } else {
          setError("Bio >= 50 simbols");
          return false
        }
      }
  

  const validateAge = (inputAge) => {
    if (/^\d+$/.test(inputAge) && inputAge.length <= 2) {
      setError('');
      return true;
    } else {
      setError('Age only alpha-numeric and <100');
      return false;
    }
  };

  const handleFileChange = (e) => {
    const file = e.target.files[0];
    setSelectedFile(file);
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (validateName(name) && validateAge(age) && validateBio(bio)) {
      console.log('Data send to server:', name, age, gender, orientation, city, bio);
      if (selectedFile) {
        console.log('Upload file:', selectedFile);
      }
    }
  };

  return (
    <div className="registration-page">
      <h1>Welcome</h1>
      <div className="form-group-center">
          <button type="submit">
          <label htmlFor="file" className="upload-button">
            <p className='start-search-button' type='submit'>Choose Your Photo</p>
        </label>
      <input
        type="file"
        id="file"
        accept="image/*"
        style={{ display: 'none' }}
        onChange={handleFileChange}
      />
          </button>
          </div>
      <div className="image-preview">
        {selectedFile ? (
          <img src={URL.createObjectURL(selectedFile)} alt="Profile" />
        ) : (
          <div className="placeholder">Preview</div>
        )}
      </div>
      <form onSubmit={handleSubmit}>
      <div className="form-group">
          <label htmlFor="name">Name:</label>
          <input
            type="text"
            id="name"
            value={name}
            placeholder='Enter you Name'
            onChange={(e) => setName(e.target.value)}
            required
          />
        </div>
        <div className="form-group">
          <label htmlFor="age">Age:</label>
          <input
            type="text"
            id="age"
            value={age}
            placeholder='Enter your Age'
            onChange={(e) => setAge(e.target.value)}
            required
          />
        </div>
        <div className="form-group">
          <label htmlFor="gender">Gender:</label>
          <select
            id="gender"
            value={gender}
            onChange={(e) => setGender(e.target.value)}
            required
          >
            <option value="">Select Gender</option>
            <option value="Male">Male</option>
            <option value="Female">Female</option>
            {/* <option value="Non-Binary">Non-Binary</option>
            <option value="Transgender">Transgender</option> */}
            {/* <option value="Other">Other</option> */}
          </select>
        </div>
        <div className="form-group">
          <label htmlFor="orientation">Orientation:</label>
          <select
            id="orientation"
            value={orientation}
            onChange={(e) => setOrientation(e.target.value)}
            required
          >
            <option value="">Select Orientation</option>
            <option value="Heterosexual">Straight</option>
            <option value="Homosexual">Bi</option>
            <option value="Bisexual">Gay</option>
            {/* <option value="Heterosexual">Heterosexual</option>
            <option value="Homosexual">Homosexual</option>
            <option value="Bisexual">Bisexual</option>
            <option value="Pansexual">Pansexual</option>
            <option value="Asexual">Asexual</option> */}
          </select>
        </div>
        <div className="form-group">
          <label htmlFor="city">City:</label>
          <select
            id="city"
            value={city}
            onChange={(e) => setCity(e.target.value)}
            required
          >
            <option value="">Select City</option>
            <option value="New York">Moscow</option>
            <option value="Los Angeles">Rome</option>
            <option value="London">New York</option>
            {/* <option value="New York">New York</option>
            <option value="Los Angeles">Los Angeles</option>
            <option value="London">London</option>
            <option value="Paris">Paris</option>
            <option value="Tokyo">Tokyo</option> */}
          </select>
        </div>
        <div className="form-group">
          <label htmlFor="bio">Bio:</label>
          <textarea
            id="bio"
            value={bio}
            placeholder='Enter your Bio'
            onChange={(e) => setBio(e.target.value)}
          ></textarea>
        </div>
        {error && <p className="error">{error}</p>}
        <div className="form-group-center">
          <button type="submit">Start Search</button>
        </div>
      </form>
    </div>
  );
}

export default RegistrationPage;
