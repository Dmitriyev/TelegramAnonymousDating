import React, { Component } from 'react';

class RegistrationPage extends Component {
  constructor() {
    super();
    this.state = {
      name: '',
      age: '',
      sex: 'male',
      orientation: 'straight',
      city: 'unknown',
      bio: '',
      profilePhoto: null,
    };
  }

  handleInputChange = (e) => {
    const { name, value } = e.target;
    this.setState({ [name]: value });
  }

  handleFileChange = (e) => {
    const file = e.target.files[0];
    this.setState({ profilePhoto: file });
  }

  handleSubmit = (e) => {
    e.preventDefault();
    // Send to server
    const handleSubmit  = () => {
        console.log(Name,lastName,email,password,confirmPassword);
    }

    return(
        <div class="container">
        <div class="row main-form">
        <form class="" method="post" action="#">
        
        <div class="form-group">
        <label for="name" class="cols-sm-2 control-label">Name</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-user fa" aria-hidden="true"></i></span>
        <input type="text" class="form-control" name="name" id="name" placeholder="Enter your Name"/>
        </div>
        </div>
        </div>
       
        <div class="form-group">
        <label for="age" class="cols-sm-2 control-label">Age</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-envelope fa" aria-hidden="true"></i></span>
        <input type="number" class="form-control" name="age" id="age" placeholder="Enter your Age"/>
        </div>
        </div>
        </div>
       
        <div class="form-group">
        <label for="sex" class="cols-sm-2 control-label">Sex</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-users fa" aria-hidden="true"></i></span>
        <select 
              name="sex"
              value={this.state.sex}
              onChange={this.handleInputChange}
            >
              <option value="male">Man</option>
              <option value="female">Women</option>
              <option value="other">Other</option>
            </select>
        </div>
        </div>
        </div>
       
        <div class="form-group">
        <label for="orientation" class="cols-sm-2 control-label">Orientation</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-lock fa-lg" aria-hidden="true"></i></span>
        <select
              name="orientation"
              value={this.state.orientation}
              onChange={this.handleInputChange}
            >
              <option value="straight">Hetero</option>
              <option value="gay">Gay</option>
              <option value="bisexual">Bi</option>
              <option value="other">Other</option>
            </select>   
        </div>
        </div>
        </div>
       
        <div class="form-group">
        <label for="city" class="cols-sm-2 control-label">City</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-lock fa-lg" aria-hidden="true"></i></span>
        <select
              name="city"
              value={this.state.city}
              onChange={this.handleInputChange}
            >
              <option value="city1">New Orsk</option>
              <option value="city2">Maskvabad</option>
              <option value="city2">Chechnya</option>
              {/* if need more cityzen */}
            </select>
        </div>
        </div>
        </div>

        <div class="form-group">
        <label for="bio" class="cols-sm-2 control-label">Bio</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-user fa" aria-hidden="true"></i></span>
        <input type="text" class="form-control" name="bio" id="bio" placeholder="Enter your Bio"/>
        </div>
        </div>
        </div>
       
        <div class="form-group ">
        <a href="#" target="_blank" type="button" id="button" class="btn btn-primary btn-lg btn-block login-button">Register</a>
        </div>
        
        </form>
        </div>
        </div>
       
    )       
}
}
export default RegistrationForm;
