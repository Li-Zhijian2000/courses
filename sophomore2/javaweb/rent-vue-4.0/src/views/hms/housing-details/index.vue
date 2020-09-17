<template>
  <div class="app-container" style="margin-top: 50px;">
    <el-row type="flex" justify="center">
      <el-col :span="8">
        <el-image
          style="width: 350px; height: 400px;"
          :src="url"
          :fit="fit"
        />
      </el-col>
      <el-col :span="3" />
      <el-col :span="8">
        <el-form ref="housing" :model="housing">
          <el-form-item label="租金">{{ housing.rent }}</el-form-item>
          <el-form-item label="房屋类型">{{ housing.nLivingroom }}厅{{ housing.nToilet }}卫{{ housing.nBedroom }}卧   {{ housing.area }} m&sup2</el-form-item>
          <el-form-item label="朝向楼层">{{ housing.towards }}  {{ housing.floor }}层</el-form-item>
          <el-form-item label="所在小区">{{ housing.community }}</el-form-item>
          <el-form-item label="所属区域">{{ housing.city }}    {{ housing.county }}    {{ housing.region }}</el-form-item>
          <el-form-item label="详细地址">{{ housing.address }}</el-form-item>
          <el-form-item label="联系电话">{{ housing.telephone }}</el-form-item>
        </el-form>
      </el-col>
    </el-row>
    <el-row>
      <h3>详细信息</h3>
        dgd
    </el-row>
  </div>
</template>

<script>
  export default {
    data() {
      return {
        housing: null,
        fit: 'fill',
        url: 'https://fuss10.elemecdn.com/e/5d/4a731a90594a4af544c0c25941171jpeg.jpeg'
      }
    },
    methods: {
      getHousing() {
        this.getRequest('/housing', { id: this.$route.params.id }).then(resp => {
          console.log(resp.data)
          this.housing = resp.data
        })
      },
    },
    created() {
      this.getHousing()
    }
  }
</script>